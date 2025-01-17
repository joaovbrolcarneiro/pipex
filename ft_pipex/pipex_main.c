#include "pipex.h"

void exit_with_error(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}
int main(int argc, char **argv, char **envp)
{
    int pipe_fd[2];
    int infile_fd, outfile_fd;
    pid_t pid1, pid2;

    if (argc != 5)
    {
        write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
        return (EXIT_FAILURE);
    }

    // Create pipe first
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed");
        return (EXIT_FAILURE);
    }

    // Then open files
    if (open_files(argv[1], argv[4], &infile_fd, &outfile_fd) < 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return (EXIT_FAILURE);
    }

    // First child
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("First fork failed");
        return (EXIT_FAILURE);
    }
    
    if (pid1 == 0)
    {
        // First child needs write end of pipe
        close(pipe_fd[0]);           // Close read end
        close(outfile_fd);           // Close unused outfile
        handle_child(argv[2], infile_fd, pipe_fd[1], envp);
    }

    // Second child
    pid2 = fork();
    if (pid2 < 0)
    {
        perror("Second fork failed");
        return (EXIT_FAILURE);
    }
    
    if (pid2 == 0)
    {
        // Second child needs read end of pipe
        close(pipe_fd[1]);           // Close write end
        close(infile_fd);            // Close unused infile
        handle_child(argv[3], pipe_fd[0], outfile_fd, envp);
    }

    // Parent process closes all file descriptors
    close(infile_fd);
    close(outfile_fd);
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for children
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return (EXIT_SUCCESS);
}