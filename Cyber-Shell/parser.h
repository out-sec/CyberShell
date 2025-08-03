#pragma once
#include <string>
#include <vector>

enum class CommandType {
    NORMAL,     // Single command
    AND,        // &&
    OR,         // ||
    SEQUENTIAL  // ;
};

struct ParsedCommand {
    std::vector<std::string> args;      // Command and arguments
    CommandType type = CommandType::NORMAL;  // Chaining type
};

// Parses full input string into a list of parsed commands
std::vector<ParsedCommand> parse_input(const std::string& input);
