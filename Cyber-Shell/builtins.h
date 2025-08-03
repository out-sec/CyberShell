#ifndef BUILTINS_H
#define BUILTINS_H

#include <vector>
#include <string>

int shell_cd(const std::vector<std::string>& args);
int shell_exit(const std::vector<std::string>& args);
int shell_pwd(const std::vector<std::string>& args);
int shell_help(const std::vector<std::string>& args);
int shell_mkdir(const std::vector<std::string>& args);
int shell_rmdir(const std::vector<std::string>& args);
int shell_touch(const std::vector<std::string>& args);
int shell_clear(const std::vector<std::string>& args);
int shell_echo(const std::vector<std::string>& args);
int shell_apt_update(const std::vector<std::string>& args);
int shell_apt_upgrade(const std::vector<std::string>& args);

#endif
