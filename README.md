# 🦾 CyberShell - Advanced Custom Linux Shell

CyberShell is a feature-rich, user-friendly custom shell built in C++ that mimics basic behavior of Unix/Linux shells like `bash` or `zsh`, while integrating colorful prompts, command history logging, aliasing, motivational banners, and custom easter eggs. It is intended for educational use, C++ system-level learning, and personal productivity enhancement.

---

## 📜 Table of Contents

- [Features](#-features)
- [Demonstration](#-demonstration)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Easter Eggs](#-easter-eggs)
- [Project Structure](#-project-structure)
- [License](#-license)

---

## 🚀 Features

- 🧠 **Command Parsing** with support for `&&`, `||`, and `;`
- 📂 **Built-in Commands**: `cd`, `exit`, `pwd`, `mkdir`, `rmdir`, `touch`, `clear`, `echo`, `help`
- 🔧 **System Update Commands**: `apt_update`, `apt_upgrade`
- 💡 **Aliases**: Define custom command aliases (`alias ll="ls -la"`)
- 📄 **Command Logging**: Every executed command is logged with timestamp and username
- ⏱ **Execution Timer**: Shows how long each command took
- 🎨 **Colorized Prompt**: Stylish prompt with user, time, and working directory
- 🔐 **Command Input Validation**: Handles overly long inputs gracefully
- ✨ **Motivational Banner**: Displayed randomly at shell startup
- 🐣 **Easter Eggs**: Fun hidden messages for special commands like `batman`, `joker`, `alexander`, etc.
- 🛑 **Signal Handling**: Handles `Ctrl+C` (SIGINT) and `Ctrl+Z` (SIGTSTP) gracefully

---

## ✅ Requirements

CyberShell is developed and tested on **Linux** (Kali/Debian-based) systems.

| Requirement         | Version / Details          |
|---------------------|----------------------------|
| GCC / g++ Compiler  | `g++` (v9.0 or above)      |
| OS                  | Linux (Debian/Kali/Ubuntu) |
| Library             | `libreadline-dev`          |
| Make (optional)     | For build automation       |

### 📦 Install dependencies

```bash
sudo apt update
sudo apt install build-essential libreadline-dev
```
⚙️ Installation
1. Clone the repository
```bash
https://github.com/Asad-channar/CyberShell.git
cd CyberShell
```
2. Compile
 ```bash
g++ main.cpp executor.cpp parser.cpp builtins.cpp alias.cpp log.cpp -o cybershell -lreadline
```
🚦 Usage
Launch the shell by running:
```bash
./cybershell
```
You will be greeted with a welcome banner and motivational quote, then dropped into your custom prompt.

🐣 Easter Eggs
The shell includes fun command easter eggs for:
```bash
batman 🦇

joker 🃏

superman 🦸

osman 🗡️

ertugrul ⚔️

hitler 👿

alexander 🛡️

aurangzeb 👑

napoleon 🎖️
```
These commands print special quotes or lines.

📁 Project Structure
```bash
CyberShell/
├── main.cpp           # Entry point
├── executor.cpp       # Executes parsed commands
├── parser.cpp         # Parses command strings
├── builtins.cpp       # Built-in command implementations
├── alias.cpp          # Alias management
├── log.cpp            # Command logging module
├── *.h                # Header files for all components
├── .au_shell_history  # Logged command history
└── README.md          # This file
```


📄 License
This project is licensed under the MIT License.

Built with ❤️ by [Asad Muhammad Channar] — Always pushing limits with C++
