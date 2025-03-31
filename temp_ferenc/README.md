# Pipex

## Introduction

Pipex is a project inspired by the shell pipeline feature (`|`). It replicates the behavior of:

```bash
< infile cmd1 | cmd2 > outfile
```

Where:
- `infile` is the input file.
- `cmd1` is the first command to be executed.
- `cmd2` is the second command to be executed.
- `outfile` is the output file.

The project uses Unix system calls such as `pipe()`, `fork()`, `dup2()`, and `execve()` to achieve this functionality.

---

## Compilation

Compile the project using:

```bash
make
```

This will generate the `pipex` executable.

---

## Usage

Run the program as follows:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

For example:

```bash
./pipex input.txt "ls -l" "wc -l" output.txt
```

This will execute:

```bash
< input.txt ls -l | wc -l > output.txt
```

---

## Code Breakdown

### **Main Execution (`pipex.c`)**

1. **Error Handling:** If incorrect arguments are provided, the program exits with a usage message.
2. **`create_pipex()` Function:**
   - Opens the necessary input and output files.
   - Creates a pipe using `pipe()`.
   - Forks two child processes to execute `cmd1` and `cmd2`.
   - Waits for both child processes to finish.

### **Command Execution (`execute_cmd()`)**

- Splits the command into an argument array using `ft_split()`.
- Finds the executable path using `get_cmd_path()`.
- Executes the command with `execve()`.

### **File and Pipe Management (`utilities.c` & `utilities2.c`)**

- `open_files()`: Opens `infile` and `outfile` with the correct permissions.
- `first_child_process()`: Redirects input to `cmd1`, writes to the pipe.
- `second_child_process()`: Reads from the pipe, redirects output to `cmd2`.
- `close_pipes_and_wait()`: Closes all pipes and waits for both processes.

### **Command Path Resolution (`get_cmd_path()`)**

- Retrieves the `PATH` environment variable.
- Splits it into directories.
- Iterates through them to find the correct path to the command.

---

## Error Handling

- If any system call fails (`pipe()`, `fork()`, `execve()`), an error message is printed, and the program exits.
- If a command is not found, an appropriate error message is displayed.

---

## Conclusion

This project demonstrates process creation, inter-process communication using pipes, and executing shell commands programmatically.

---

## Credits

Project developed as part of 42 School's curriculum.

