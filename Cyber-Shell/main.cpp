#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include <csignal>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <regex>

#include "parser.h"
#include "executor.h"
#include "alias.h"
#include "log.h"

// Signal flags
volatile sig_atomic_t got_sigint = 0;
volatile sig_atomic_t got_sigtstp = 0;

// Motivational Quotes
const std::vector<std::string> quotes = {
    "💬 Dream big. Start small. Act now.",
    "💬 Stay hungry, stay foolish.",
    "💬 Believe you can and you're halfway there.",
    "💬 Push yourself, because no one else is going to do it for you.",
    "💬 Great things never come from comfort zones.",
    "💬 Success doesn’t come to you. You go to it."
};

// Expand $VAR environment variables
std::string expand_variables(const std::string& input) {
    std::regex var_pattern(R"(\$([A-Za-z_][A-Za-z0-9_]*))");
    std::string result;
    std::sregex_iterator it(input.begin(), input.end(), var_pattern);
    std::sregex_iterator end;

    size_t last_pos = 0;
    for (; it != end; ++it) {
        result += input.substr(last_pos, it->position() - last_pos);
        const char* val = getenv((*it)[1].str().c_str());
        result += val ? val : it->str();
        last_pos = it->position() + it->length();
    }

    result += input.substr(last_pos);  // Append remaining part of the string
    return result;
}

void show_banner() {
    std::cout << "\033[1;36m" // Cyan bold
              << "\n Welcome to CyberShell ⚔️\n"
              << quotes[rand() % quotes.size()] << "\n"
              << "\033[0m\n\n"; // Reset
}

// Prompt: user@hostname:/path [HH:MM] $
std::string get_prompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    std::time_t now = std::time(nullptr);
    char time_buf[6];
    std::strftime(time_buf, sizeof(time_buf), "%H:%M", std::localtime(&now));

    std::string user = getenv("USER") ? getenv("USER") : "user";
    std::string path = cwd;
    std::string hostname = "localhost";
    char host[256];
    if (gethostname(host, sizeof(host)) == 0)
        hostname = host;

    return "\001\033[1;37m\002" + user + "@" + hostname + ":" + path +
       " [" + time_buf + "] [CyberShell ⚔️] $ \001\033[0m\002";
}

// Signal handlers
void handle_sigint(int sig) {
    got_sigint = 1;
}
void handle_sigtstp(int sig) {
    got_sigtstp = 1;
}

int main() {
    using_history();
    srand(time(nullptr));
    show_banner();
    initialize_aliases();

    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, handle_sigtstp);

    while (true) {
        if (got_sigint) {
            std::cout << "\n[!] Ctrl+C pressed. Interrupt ignored.\n";
            got_sigint = 0;
        }
        if (got_sigtstp) {
            std::cout << "\n[!] Ctrl+Z pressed. Suspend ignored.\n";
            got_sigtstp = 0;
        }

        std::string prompt = get_prompt();
        char* input = readline(prompt.c_str());
        if (!input) break;

        std::string line = input;
        free(input);

        if (line.empty()) continue;

        if (line[0] == 24) { // Ctrl+X ASCII
            std::cout << "[!] Ctrl+X detected (ASCII 24). You can assign custom logic here.\n";
            continue;
        }

        line = resolve_alias(line);        //  Alias substitution
        line = expand_variables(line);     //  Expand $VARs

        add_history(line.c_str());
        log_command(line);

        auto commands = parse_input(line);
        run_command(commands);
    }

    return 0;
}
