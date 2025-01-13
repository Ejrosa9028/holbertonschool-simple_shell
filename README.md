# Simple Shell Project

## Project Overview

The Simple Shell project is a custom implementation of a Unix shell. It replicates the behavior of `/bin/sh` and allows users to execute commands interactively or non-interactively. This project is part of the curriculum at Holberton School and aims to strengthen the understanding of system calls, memory management, and process handling.

## Purpose

The purpose of this project is to:

- Understand how a Unix shell works internally.
- Gain hands-on experience with system calls, process management, and I/O redirection.
- Improve programming skills in C by building a functional shell.

## Main Features

- Displays a prompt and waits for user input.
- Executes commands with or without arguments.
- Resolves commands using the `PATH` environment variable.
- Handles errors gracefully and supports Ctrl+D (EOF).
- Implements built-in commands like `exit` and `env`.

## Current Implementation

**Task 0:**
- Created `README.md`, `simple_shell.1` (man page), and `AUTHORS` files.

**Task 1:**
- Code complies with the Betty coding style guidelines.

**Task 2:**
- Displays a prompt and waits for user commands.
- Executes simple commands without arguments.
- Handles errors gracefully.
- Supports the Ctrl+D EOF condition.

**Task 3:**
- Executes commands with arguments.

**Task 4:**
- Resolves commands using the `PATH` variable.
- Ensures `fork()` is not called if a command doesn’t exist.

**Task 5:**
- Implements the `exit` built-in command to terminate the shell.

**Task 6:**
- Implements the `env` built-in to display the current environment.

## Intended Audience

This project is designed for:

- Students and professionals interested in system programming.
- Individuals seeking to deepen their knowledge of Unix-like operating systems.
- Developers exploring how command-line interfaces work.

## Compilation Instructions

To compile the shell, use:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell
```
## Contributors

Diego Mercado [Github profile](https://github.com/DMC254) | [Linkin](https://www.linkedin.com/in/diego-mercado-6040a9336/)
Emanuel Rosa [Github profile](https://github.com/Ejrosa9028) | [Linkin](https://www.linkedin.com/in/emanuel-j-rosa-alamo-0a1615329/)
