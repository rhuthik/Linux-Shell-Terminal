# Linux-Shell
Custom terminal shell based on the POSIX architecture with integrated syscalls and in-built commands. Supports piping, redirection and signal handling.

## Features

- Execute commands: Enter program names and arguments to run external programs.
- Change directory: Use the `cd` command to navigate the file system.
- Built-in functions: The shell provides helpful built-in functions such as `help` and `exit`.
- Pipes: Support for executing commands with piping.
- Redirection: Redirect command output to a file.

## Getting Started

To get started with Turtle Shell, follow these steps:

1. Clone the repository: `git clone https://github.com/rhuthik/Linux-Shell-Terminal`
2. Compile the code: `gcc turtle.c -o turtle`
3. Run the shell: `./turtle`

## Usage

Once you have the shell running, you can enter commands similar to a regular shell. Here are some examples:

- Run an external program: `ls -l`
- Change directory: `cd /path/to/directory`
- Make directory: mkdir test
- Remove directory: rmdir test
- View built-in help: `help`
- Exit the shell: `exit`

## Built-in Functions

Turtle Shell provides the following built-in functions:

- `cd [directory]`: Change the current working directory. If no directory is specified, it prints an error message.
- `help`: Display a list of built-in functions and usage information.
- `exit`: Exit the shell.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgements

- The Turtle Shell project was inspired by the Unix shell and aims to provide a simple implementation for educational purposes.

