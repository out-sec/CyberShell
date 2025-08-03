#include "parser.h"
#include <sstream>
#include <iostream>

std::vector<ParsedCommand> parse_input(const std::string& input) {
    const size_t MAX_INPUT_SIZE = 1024;

    if (input.size() > MAX_INPUT_SIZE) {
        std::cerr << "Error: Input exceeds maximum size (" << MAX_INPUT_SIZE << " bytes).\n";
        return {};
    }

    std::vector<ParsedCommand> commands;
    std::istringstream iss(input);
    std::string token;

    ParsedCommand currentCmd;
    CommandType nextType = CommandType::NORMAL;

    while (iss >> token) {
        if (token == "&&" || token == "||" || token == ";") {
            if (!currentCmd.args.empty()) {
                currentCmd.type = nextType;
                commands.push_back(currentCmd);
                currentCmd = ParsedCommand();
            }

            if (token == "&&")
                nextType = CommandType::AND;
            else if (token == "||")
                nextType = CommandType::OR;
            else
                nextType = CommandType::SEQUENTIAL;

        } else {
            currentCmd.args.push_back(token);
        }
    }

    if (!currentCmd.args.empty()) {
        currentCmd.type = nextType;
        commands.push_back(currentCmd);
    }

    return commands;
}
