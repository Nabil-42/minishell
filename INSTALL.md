# Installation — minishell

## System Requirements

- **OS**: Linux or macOS
- **Compiler**: `gcc` or `clang` with C99 support
- **readline**: development headers required
  - Ubuntu/Debian: `sudo apt install libreadline-dev`
  - macOS (Homebrew): `brew install readline`
- **Make**

## Build

```bash
git clone https://github.com/Nabil-42/minishell.git
cd minishell
make
```

The compiled binary will be at `./minishell`.

## Clean

```bash
make clean    # remove object files
make fclean   # remove object files and binary
make re       # full rebuild
```

## Norminette

All source files comply with the 42 Norminette coding standard:

```bash
norminette src/ includes/
```
