# Changelog — minishell

All notable changes to the minishell project.

## [1.0.0] — 2025

### Added
- Interactive prompt with command history via `readline`
- Lexer: tokenize input into words, operators, and quoted strings
- Parser: build command table from token stream
- Executor: fork + execve for external commands
- Pipe chaining: connect multiple commands with `pipe()` and `dup2()`
- Redirections: `<`, `>`, `>>`, and `<<` (heredoc)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling (no expansion in single quotes)
- Signal handling: `Ctrl-C` (SIGINT), `Ctrl-D` (EOF), `Ctrl-\` (SIGQUIT)
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Exit status propagation (`$?`)
- Memory management: no leaks on normal execution paths (checked with Valgrind)
