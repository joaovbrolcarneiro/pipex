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

    cmd_path = get_env_path(envp, args[0]);
    if (!cmd_path)
    {
        // Print error with format: pipex: <command>: command not found
        fprintf(stderr, "pipex: %s: command not found\n", args[0]);
        free(args);
        exit(EXIT_FAILURE); // Exit after error
    }

    // Execute the command
    if (execve(cmd_path, args, envp) == -1)
    {
        // Handle errors during execve
        if (errno == EACCES)
            fprintf(stderr, "pipex: %s: permission denied\n", args[0]);
        else
            fprintf(stderr, "pipex: %s: %s\n", args[0], strerror(errno));  // Print error message for other cases
        free(args);
        free(cmd_path);
        exit(EXIT_FAILURE);
    }

    // If execve returns, there was an error
    free(args);
    free(cmd_path);
    exit(EXIT_FAILURE);
}
