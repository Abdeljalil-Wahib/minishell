🐚 Minishell

A simple UNIX shell implementation written in C — built as part of the 42 School curriculum.
Recreating a tiny version of bash with command parsing, pipes, redirections, and built-in commands.

🚀 Features

✅ Interactive prompt — works like a real shell
✅ Built-in commands — cd, echo, pwd, export, unset, env, exit
✅ Command execution — handles absolute & relative paths
✅ Pipes & Redirections — |, <, >, >>
✅ Environment variables — supports $VAR expansion
✅ Signal handling — CTRL+C, CTRL+D, CTRL+\
✅ History support — powered by readline
✅ Error handling — descriptive and user-friendly

📦 Installation
1. Clone the Repository
git clone https://github.com/yourusername/minishell.git
cd minishell

2. Build the Project
make

3. Run Minishell
./minishell

🛠 Requirements

C Compiler (gcc or clang)

GNU Readline library

Install Readline on Linux (Debian/Ubuntu):
sudo apt update
sudo apt install libreadline-dev

Install Readline on macOS (Homebrew):
brew install readline

💻 Usage Examples
$ ./minishell
🐚 minishell$ echo "Hello, World!"
Hello, World!

🐚 minishell$ export NAME=WAHIB
🐚 minishell$ echo "Hi $NAME"
Hi WAHIB

🐚 minishell$ ls -l | grep minishell
-rwxr-xr-x  1 aj  staff  42000 Aug 20 22:10 minishell

🧪 Testing

Run a few commands to check everything works:

./minishell
🐚 minishell$ echo Hello
Hello

🐚 minishell$ ls | wc -l
42

🐚 minishell$ cat < infile | grep minishell > outfile

📌 Authors

Mohammed Ouzerzou — [1337 Student]
Abdeljalil-wahib — [1337 Student]



⭐ Acknowledgements
GNU Readline
Bash Manual
1337 Coding School
