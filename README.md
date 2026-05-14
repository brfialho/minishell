*This project was created as part of the 42 curriculum by rafreire, brfialho.*

# 🔥 Minishell 🔥

A simple shell implementation written in C, replicating core functionalities of bash.

---

## Description

**Minishell** is a minimalist Unix shell that interprets and executes commands, providing an interactive command-line interface. This project aims to deepen understanding of process management, file descriptors, signal handling, and parsing techniques in C.

### Key Features

- **Command Execution**: Execute binaries from `PATH` or absolute/relative paths
- **Built-in Commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Pipes**: Chain commands using `|` operator
- **Redirections**: Input (`<`), output (`>`), append (`>>`), and heredoc (`<<`)
- **Logical Operators**: `&&` and `||` for conditional command execution
- **Environment Variables**: Expansion of `$VAR` and `$?` (last exit status)
- **Quote Handling**: Single (`'`) and double (`"`) quotes with proper expansion rules
- **Signal Handling**: `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` behave like bash
- **Command History**: Navigate through previous commands using arrow keys

---

## Instructions

### Prerequisites

- **GCC** or **Clang** compiler
- **GNU Make**
- **Readline library** (with development headers)

On Debian/Ubuntu, install readline with:
```bash
sudo apt-get install libreadline-dev
```

On macOS with Homebrew:
```bash
brew install readline
```

### Compilation

Clone the repository and compile using `make`:

```bash
git clone --recurse-submodule https://github.com/brfialho/minishell.git
cd minishell
make
```

This will generate the `minishell` executable.

### Available Make Commands

| Command       | Description                                      |
|---------------|--------------------------------------------------|
| `make`        | Compile the project                              |
| `make clean`  | Remove object files                              |
| `make fclean` | Remove object files and executable               |
| `make re`     | Recompile from scratch                           |
| `make leaks`  | Run with Valgrind for memory leak detection      |
| `make test`   | Custom test suite with unitary tests		       |

### Test suite

The project includes a custom unit test suite focused on validating some of the most critical shell components.

Current test coverage includes:

Lexer tokenization
Parser behavior and AST generation
Expansion logic and environment variable handling

Run the tests with:

```bash
make test
```

The tests are designed to help validate parser correctness and prevent regressions during development.

### Running

After compilation, start the shell:

```bash
./minishell
```

### Usage Examples

```bash
# Simple command execution
🔥Minihell🔥 /path$ ls -la

# Pipes
🔥Minihell🔥 /path$ cat file.txt | grep "pattern" | wc -l

# Redirections
🔥Minihell🔥 /path$ echo "Hello World" > output.txt
🔥Minihell🔥 /path$ cat < input.txt >> output.txt

# Heredoc
🔥Minihell🔥 /path$ cat << EOF
> Line 1
> Line 2
> EOF

# Environment variables
🔥Minihell🔥 /path$ echo $HOME
🔥Minihell🔥 /path$ export MY_VAR="value"
🔥Minihell🔥 /path$ echo $MY_VAR

# Logical operators
🔥Minihell🔥 /path$ ls && echo "Success"
🔥Minihell🔥 /path$ false || echo "Fallback"

# Exit with status code
🔥Minihell🔥 /path$ exit 42
```

---

## Project Architecture

```
minishell/
├── includes/          # Header files
├── libft/             # Custom C library
├── srcs/
│   ├── builtins/      # Built-in command implementations
│   ├── env/           # Environment variable management
│   ├── execution/     # Command execution, pipes, redirections
│   ├── expansion/     # Variable and quote expansion
│   ├── heredoc/       # Heredoc handling
│   |── lexer/         # Tokenization
│   |── parser/        # AST construction
│   ├── prompt/        # Prompt display
│   └── signals/       # Signal handling
└── tests/             # Test suite
```

---

## Resources

### Documentation & References

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) - Official GNU Bash documentation
- [Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/readline.html) - GNU Readline manual

### Tutorials & Articles

- [Let's Build a Linux Shell - Part I](https://brennan.io/2015/01/16/write-a-shell-in-c/) - Stephen Brennan

### AI Usage

AI tools (GitHub Copilot) were used in this project for:
- **Code architecture**: Assistance in planning the workflow desing.
- **Documentation**: Assistance in writing comments and this README
- **Debugging assistance**: Identifying potential issues and suggesting fixes
- **Research**: Quick lookups on system calls and library functions

---

## Authors

 - [**rafreire**](https://github.com/AlmeidaRafaelFeh)
 - [**brfialho**](https://github.com/brfialho)

---

## License

This project is part of the 42 School curriculum. All rights reserved.
