# Minishell
Minishell is a simple shell implemented in C language, mimicking the functionality of the Bash shell. This minishell has implemented the following key features:

1. Redirection Features
  * <: Input redirection
  * <<: Input redirection (here document)
  * >: Output redirection
  * >>: Output redirection (overwrite)
2. Pipe Feature
  * |: Communication between commands using pipes
3. Environment Variable Feature
  * $: Using environment variables
4. Signal Handling Features
  * Ctrl+C: Program termination signal
  * Ctrl+D: EOF (End Of File) signal
  * Ctrl+\: Quit signal
5. Extended Echo Feature
  * Echo command with -n option to remove trailing newline character
6. CD Command
  * Can only use relative or absolute paths
7. PWD Command
  * Print the current working directory if no options are provided
8. Export Command
  * Setting environment variables
9. Unset Command
  * Removing environment variables
10. Env Command
  * Print environment variables if no options or arguments are provided
11. Exit Command
  * Exit the shell if no options or arguments are provided

# Usage
1. Run the minishell: ./minishell
2. Input commands: You can input any Bash shell commands available.
3. Exit: Use the exit command or Ctrl+D to exit the minishell.

# Example
```
$ ./minishell
$ ls -l > output.txt
$ cat < input.txt | grep "pattern"
$ echo -n "Hello, World!"
$ cd /path/to/directory
$ export MY_VARIABLE=my_value
$ unset MY_VARIABLE
$ env
$ exit
```
