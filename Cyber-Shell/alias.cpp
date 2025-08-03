#include "alias.h"
#include <unordered_map>
#include <sstream>
#include <vector>

static std::unordered_map<std::string, std::string> alias_map;

// Define your aliases here
void initialize_aliases() {
    alias_map["ll"] = "ls -la";
    alias_map["gs"] = "git status";
    alias_map[".."] = "cd ..";
    alias_map["list"] = "ls";
    alias_map["myip"] = "ip addr";
    alias_map["update"] = "sudo apt update && sudo apt upgrade -y";
    alias_map["print"] = "echo";
    alias_map["shutdown"] = "poweroff";
    alias_map["restart"] = "reboot";
    alias_map["datetime"] = "timedatectl";
    // Add more aliases here
}

// Split input into tokens
std::vector<std::string> split_input(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Resolve aliases
std::string resolve_alias(const std::string& input) {
    auto tokens = split_input(input);
    if (tokens.empty()) return input;

    auto it = alias_map.find(tokens[0]);
    if (it != alias_map.end()) {
        // Replace first token with alias
        std::ostringstream resolved;
        resolved << it->second;
        for (size_t i = 1; i < tokens.size(); ++i) {
            resolved << " " << tokens[i];
        }
        return resolved.str();
    }
    return input;
}
