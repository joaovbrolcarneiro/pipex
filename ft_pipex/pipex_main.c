/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:34:28 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/21 14:41:51 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_with_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

static void	close_all_fds(int *pipe_fd, int infile_fd, int outfile_fd)
{
	close(infile_fd);
	close(outfile_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

/*static int	initialize_pipes_and_files(int argc, char **argv,
			int *pipe_fd, int *fds)
{
	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
		return (EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		return (EXIT_FAILURE);
	}
	if (open_files(argv[1], argv[4], &fds[0], &fds[1]) < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}*/

/*static int	create_processes(char **argv, int *pipe_fd,
			int *fds, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 < 0)
		return (EXIT_FAILURE);
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		close(fds[1]);
		handle_child(argv[2], fds[0], pipe_fd[1], envp);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (EXIT_FAILURE);
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		close(fds[0]);
		handle_child(argv[3], pipe_fd[0], fds[1], envp);
	}
	return (EXIT_SUCCESS);
}*/

int main(int argc, char **argv, char **envp)
{
    int pipe_fd[2];
    int fds[2];
    int status1, status2;
    pid_t pid1, pid2;

    if (argc != 5)
    {
        write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
        return (EXIT_FAILURE);
    }
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return (EXIT_FAILURE);
    }
    fds[0] = open(argv[1], O_RDONLY);
    fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fds[1] < 0)
        perror(argv[4]);  // Print error for output file

    pid1 = fork();
    if (pid1 < 0)
        return (EXIT_FAILURE);
    if (pid1 == 0)
    {
        if (fds[0] < 0)
            fds[0] = open("/dev/null", O_RDONLY);
        close(pipe_fd[0]);
        close(fds[1]);
        handle_child(argv[2], fds[0], pipe_fd[1], envp);
    }

    pid2 = fork();
    if (pid2 < 0)
        return (EXIT_FAILURE);
    if (pid2 == 0)
    {
        if (fds[1] < 0)
            fds[1] = open("/dev/null", O_WRONLY);
        close(pipe_fd[1]);
        close(fds[0]);
        handle_child(argv[3], pipe_fd[0], fds[1], envp);
    }

    close_all_fds(pipe_fd, fds[0], fds[1]);
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    // Return appropriate exit status
    if (WIFEXITED(status2))
    {
        int exit_code = WEXITSTATUS(status2);
        if (fds[1] < 0)  // If output file had permission error
            return (EXIT_FAILURE);
        return (exit_code);
    }
    return (EXIT_FAILURE);
}