#include "executor.h"
#include "parser.h"
#include "builtins.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <string>
#include <cstdlib>
#include <csignal>
#include <chrono>
#include <iomanip>

// Built-in command map
std::map<std::string, std::function<int(const std::vector<std::string>&)>> builtins = {
    {"cd", shell_cd},
    {"exit", shell_exit},
    {"help", shell_help},
    {"pwd", shell_pwd},
    {"mkdir", shell_mkdir},
    {"rmdir", shell_rmdir},
    {"touch", shell_touch},
    {"clear", shell_clear},
    {"echo", shell_echo},

    // Easter eggs
    {"batman", [](const std::vector<std::string>&) -> int {
        std::cout << "\033[1;35m🦇 I AM THE NIGHT.\033[0m\n";
        return 0;
    }},
    {"joker", [](const std::vector<std::string>&) -> int {
        std::cout << "\033[1;31m🃏 Why so serious?\033[0m\n";
        return 0;
    }},
    {"superman", [](const std::vector<std::string>&) -> int {
        std::cout << "\033[1;34m🦸‍♂️ Truth, Justice, and the AU-Shell Way.\033[0m\n";
        return 0;
    }},
    {"osman", [](const std::vector<std::string>&) -> int {
        std::cout << "\033[1;34m🦸‍♂️ Borada Bey Da Benim, Devlat Da Benim\033[0m\n";
        return 0;
    }},
    {"ertugrul", [](const std::vector<std::string>&) -> int {
        std::cout << "\033[1;34m🦸‍♂️ Ben Suleiman-Shah Oglu Ertugrul Bey.\033[0m\n";
        return 0;
    }},

    {"hitler", [](const std::vector<std::string>&) -> int {
    std::cout << "\033[1;31m⚔️  If you win, you need not have to explain... If you lose, you should not be there to explain!\033[0m\n";
    return 0;
    }},

    {"alexander", [](const std::vector<std::string>&) -> int {
        std::cout << "\033[1;36m🏺 There is nothing impossible to him who will try.\033[0m\n";
        return 0;
    }},

    {"aurangzeb", [](const std::vector<std::string>&) -> int {
        std::cout << "\033[1;32m🕌 I came alone and I go as a stranger. I do not know who I am, nor what I have been doing.\033[0m\n";
        return 0;
    }},

    {"napoleon", [](const std::vector<std::string>&) -> int {
        std::cout << "\033[1;33m🪖 Impossible is a word to be found only in the dictionary of fools.\033[0m\n";
        return 0;
    }},

    // Wrapper for system-level commands like apt
    {"apt", [](const std::vector<std::string>& args) -> int {
        pid_t pid = fork();
        if (pid == 0) {
            std::vector<char*> c_args;
            for (auto& arg : args) c_args.push_back(const_cast<char*>(arg.c_str()));
            c_args.push_back(nullptr);
            execvp(c_args[0], c_args.data());
            perror("execvp failed");
            exit(1);
        } else if (pid > 0) {
            signal(SIGINT, SIG_IGN);
            signal(SIGTSTP, SIG_IGN);
            int status;
            waitpid(pid, &status, 0);
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            return WEXITSTATUS(status);
        } else {
            perror("fork failed");
            return 1;
        }
    }},
};

// Execute a single command
int execute_single_command(const std::vector<std::string>& args) {
    if (args.empty()) return 0;

    // Check if it's a built-in command
    if (builtins.count(args[0])) {
        return builtins[args[0]](args);
    }

    // Otherwise, external command
    pid_t pid = fork();
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        std::vector<char*> c_args;
        for (const auto& arg : args)
            c_args.push_back(const_cast<char*>(arg.c_str()));
        c_args.push_back(nullptr);

        execvp(c_args[0], c_args.data());
        perror("exec");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);

        int status;
        waitpid(pid, &status, 0);

        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    } else {
        perror("fork");
        return 1;
    }
}

// Run all parsed commands with chaining logic and timing
void run_command(const std::vector<ParsedCommand>& commands) {
    int last_status = 0;

    for (const auto& cmd : commands) {
        // Start timing
        auto start = std::chrono::high_resolution_clock::now();

        // Execute the command
        last_status = execute_single_command(cmd.args);

        // End timing
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << "\033[1;33m[⏱ Took: " << std::fixed << std::setprecision(2)
                  << duration.count() << "s]\033[0m\n";

        // Logic for command chaining (&&, ||, ;)
        if (cmd.type == CommandType::AND && last_status != 0)
            break;
        if (cmd.type == CommandType::OR && last_status == 0)
            break;
    }
}
