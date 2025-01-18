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

static int	initialize_pipes_and_files(int argc, char **argv,
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
}

static int	create_processes(char **argv, int *pipe_fd,
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
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		fds[2];

	if (initialize_pipes_and_files(argc, argv, pipe_fd, fds) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_processes(argv, pipe_fd, fds, envp) == EXIT_FAILURE)
	{
		close_all_fds(pipe_fd, fds[0], fds[1]);
		return (EXIT_FAILURE);
	}
	close_all_fds(pipe_fd, fds[0], fds[1]);
	wait(NULL);
	wait(NULL);
	return (EXIT_SUCCESS);
}
