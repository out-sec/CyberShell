#pragma once
#include "parser.h"  // Defines ParsedCommand and CommandType
#include <vector>

// Main function to run parsed commands
void run_command(const std::vector<ParsedCommand>& commands);
