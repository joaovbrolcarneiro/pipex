#include "pipex.h"

int open_files(char *infile, char *outfile, int *infile_fd, int *outfile_fd)
{
    printf("Opening files: infile=%s, outfile=%s\n", infile, outfile);

    // Open the input file for reading
    *infile_fd = open(infile, O_RDONLY);
    if (*infile_fd < 0)
    {
        perror("Error opening input file");
        return -1; // Indicate failure
    }
    printf("Input file descriptor: %d\n", *infile_fd);

    // Open the output file for writing (create if it doesn't exist, truncate if it does)
    *outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*outfile_fd < 0)
    {
        perror("Error opening output file");
        close(*infile_fd); // Close input file before returning
        return -1; // Indicate failure
    }
    printf("Output file descriptor: %d\n", *outfile_fd);

    return 0; // Success
}

void setup_pipes(int pipe_fd[2])
{
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed");
        exit_with_error(ERR_PIPE);
    }
    printf("Pipe created: pipe_fd[0]=%d, pipe_fd[1]=%d\n", pipe_fd[0], pipe_fd[1]);
}
