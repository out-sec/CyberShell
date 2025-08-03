#include "builtins.h"
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstdio>

int shell_cd(const std::vector<std::string>& args) {
    const char* path = args.size() > 1 ? args[1].c_str() : getenv("HOME");
    if (chdir(path) != 0) {
        perror("cd");
        return 1;
    }
    return 0;
}

int shell_exit(const std::vector<std::string>& args) {
    std::cout << "Exiting shell...\n";
    exit(0);
}

int shell_pwd(const std::vector<std::string>& args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << cwd << std::endl;
        return 0;
    } else {
        perror("pwd");
        return 1;
    }
}

int shell_help(const std::vector<std::string>& args) {
    std::cout << "Supported built-ins: cd, exit, pwd, apt update, help, mkdir, rmdir, touch, clear, echo\n";
    return 0;
}

int shell_mkdir(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "mkdir: missing directory name\n";
        return 1;
    }
    if (mkdir(args[1].c_str(), 0755) != 0)
        perror("mkdir");
    return 0;
}

int shell_rmdir(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "rmdir: missing directory name\n";
        return 1;
    }
    if (rmdir(args[1].c_str()) != 0)
        perror("rmdir");
    return 0;
}

int shell_touch(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "touch: missing file name\n";
        return 1;
    }
    FILE* file = fopen(args[1].c_str(), "a");
    if (!file) {
        perror("touch");
        return 1;
    }
    fclose(file);
    return 0;
}

int shell_clear(const std::vector<std::string>& args) {
    system("clear");
    return 0;
}

int shell_echo(const std::vector<std::string>& args) {
    for (size_t i = 1; i < args.size(); ++i)
        std::cout << args[i] << " ";
    std::cout << std::endl;
    return 0;
}

int shell_apt_update(const std::vector<std::string>& args) {
    std::cout << "Running: sudo apt update\n";
    int result = system("sudo apt update");
    return result;
}

int shell_apt_upgrade(const std::vector<std::string>& args) {
    std::cout << "Running: sudo apt upgrade\n";
    int result = system("sudo apt upgrade");
    return result;
}

