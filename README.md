# minishell

[![Language](https://img.shields.io/badge/Language-C-A8B9CC?style=flat&logo=c)](https://github.com/Nabil-42/minishell)
[![School](https://img.shields.io/badge/%C3%89cole_42-Paris-00babc?style=flat)](https://42.fr)
[![Norminette](https://img.shields.io/badge/Norminette-compliant-brightgreen?style=flat)](https://github.com/42School/norminette)

A functional Unix shell written in C, implementing core Bash behavior including pipes, redirections, environment variables, and builtins.

## Description

`minishell` replicates the essential behavior of bash: it reads user input, parses it into commands and arguments, handles quoting and variable expansion, executes commands with pipes and redirections, and manages environment variables. The project was built in pair programming.

## Features

- Interactive prompt with command history (via `readline`)
- Single and double quote handling
- Environment variable expansion (`$VAR`, `$?`)
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Pipes: `cmd1 | cmd2 | cmd3`
- Signals: `Ctrl-C`, `Ctrl-D`, `Ctrl-\` behave as in bash

### Builtins

| Command | Description |
|---------|-------------|
| `echo` | Print arguments (`-n` flag supported) |
| `cd` | Change directory |
| `pwd` | Print working directory |
| `export` | Set environment variable |
| `unset` | Remove environment variable |
| `env` | Print environment |
| `exit` | Exit shell with status code |

## Architecture

```
readline → lexer (tokenize) → parser (AST) → executor
                                              ├── builtin? → run builtin
                                              └── external? → fork → execve
                                                  pipes → connect stdin/stdout with pipe()
                                                  redirections → dup2()
```

## Stack

- **Language**: C
- **Library**: `readline` (history, input)
- **Key concepts**: process forking (`fork`, `execve`, `waitpid`), file descriptor manipulation (`dup2`, `pipe`), lexing and parsing, signal handling

## 42 Project Info

| Field | Value |
|-------|-------|
| **Project** | minishell |
| **Circle** | 3 |
| **Norminette** | Compliant |

## What I Learned

- Full shell execution model: lexer → parser → executor
- Process management: `fork`, `execve`, `waitpid`, exit status
- File descriptor duplication and pipe chaining
- Signal handling inside a REPL
- Collaborative development (pair programming at 42)