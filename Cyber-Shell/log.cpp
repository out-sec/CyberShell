#include "log.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <pwd.h>

void log_command(const std::string& command) {
    std::string log_path = "./.cyber_shell_history";  // Log file in current directory

    // Get current time
    std::time_t now = std::time(nullptr);
    char time_str[64];
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Get username
    struct passwd* pw = getpwuid(getuid());
    std::string user = pw ? pw->pw_name : "unknown";

    // Open log file in append mode
    std::ofstream log_file(log_path, std::ios::app);
    if (log_file) {
        log_file << "[" << time_str << "] [" << user << "] " << command << "\n";
        log_file.close();
    } else {
        std::cerr << "Warning: Could not open log file for writing.\n";
    }
}
