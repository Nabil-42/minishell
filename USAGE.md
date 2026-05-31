# Usage — minishell

## Launch

```bash
./minishell
```

A prompt appears. Type commands as you would in bash.

## Supported Features

### Basic Commands

```bash
minishell$ ls -la
minishell$ cat README.md
minishell$ echo "Hello, World!"
```

### Builtins

```bash
minishell$ echo -n "no newline"
minishell$ cd /tmp
minishell$ pwd
minishell$ export MY_VAR=hello
minishell$ env
minishell$ unset MY_VAR
minishell$ exit 0
```

### Environment Variables

```bash
minishell$ echo $HOME
minishell$ echo $?          # exit status of last command
minishell$ export FOO=bar
minishell$ echo $FOO
```

### Quotes

```bash
minishell$ echo "Hello $USER"    # double quotes: variable expanded
minishell$ echo 'Hello $USER'    # single quotes: literal, no expansion
```

### Redirections

```bash
minishell$ echo hello > file.txt      # stdout to file (overwrite)
minishell$ echo hello >> file.txt     # stdout to file (append)
minishell$ cat < file.txt             # stdin from file
minishell$ cat << EOF                 # heredoc: read until delimiter
> line1
> EOF
```

### Pipes

```bash
minishell$ ls | grep .c | wc -l
minishell$ cat file.txt | sort | uniq
```

### Signals

| Signal | Behavior |
|--------|----------|
| `Ctrl-C` | Interrupt current command, new prompt |
| `Ctrl-D` | Exit shell (EOF) |
| `Ctrl-\` | No action (ignored, as in bash) |

## Exit

```bash
minishell$ exit
# or press Ctrl-D
```
