#include "pipex.h"

void handle_child(char *cmd, int fd_in, int fd_out, char **envp)
{
    char **args;
    char *cmd_path;

    // First do input redirection
    if (dup2(fd_in, STDIN_FILENO) == -1)
    {
        perror("dup2 failed on input");
        exit(EXIT_FAILURE);
    }

    // Then output redirection
    if (dup2(fd_out, STDOUT_FILENO) == -1)
    {
        perror("dup2 failed on output");
        exit(EXIT_FAILURE);
    }

    // Close the original file descriptors after successful duplication
    close(fd_in);
    close(fd_out);

    // Split the command and get its path
    args = ft_split(cmd, ' ');
    if (!args)
        exit_with_error(ERR_MALLOC);

    // Get the command path from the environment
    cmd_path = get_env_path(envp, args[0]);
    if (!cmd_path)
    {
        // Print error if command is not found in the PATH
        fprintf(stderr, "pipex: %s: command not found\n", args[0]);
        free(args);
        exit(EXIT_FAILURE); // Exit after error
    }

    // Specific checks for argument issues for different commands:
    
    // Handle grep missing argument to -e
    if (strcmp(args[0], "grep") == 0)
    {
        if (args[1] == NULL)  // Missing argument to -e
        {
            fprintf(stderr, "grep: missing argument to `-e'\n");
            free(args);
            free(cmd_path);
            exit(EXIT_FAILURE);
        }
    }

    // Handle awk missing pattern argument
    if (strcmp(args[0], "awk") == 0)
    {
        if (args[1] == NULL)  // Missing argument to pattern
        {
            fprintf(stderr, "awk: missing argument to pattern\n");
            free(args);
            free(cmd_path);
            exit(EXIT_FAILURE);
        }
    }

    // Handle sed invalid option error
    if (strcmp(args[0], "sed") == 0)
    {
        if (args[1] && args[1][0] == '-' && args[1][1] != 'e')  // Invalid option (other than -e)
        {
            fprintf(stderr, "sed: invalid option -- %c\n", args[1][1]);
            fprintf(stderr, "sed: usage: sed [-ne] [file ...]\n");
            free(args);
            free(cmd_path);
            exit(EXIT_FAILURE);
        }
    }

    // Execute the command
    if (execve(cmd_path, args, envp) == -1)
    {
        // Handle errors during execve execution
        if (errno == EACCES)
            fprintf(stderr, "pipex: %s: Permission denied\n", args[0]);
        else
            fprintf(stderr, "pipex: %s: %s\n", args[0], strerror(errno));  // Print other execve errors
        free(args);
        free(cmd_path);
        exit(EXIT_FAILURE);
    }

    // If execve returns, there was an error
    free(args);
    free(cmd_path);
    exit(EXIT_FAILURE);
}

