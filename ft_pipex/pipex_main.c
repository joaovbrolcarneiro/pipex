/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:34:28 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/22 18:56:34 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	fork_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_with_error("fork");
	return (pid);
}

static void	handle_first_child(int *pipe_fd, int *fds, char **argv, char **envp)
{
	if (fds[0] < 0)
		fds[0] = open("/dev/null", O_RDONLY);
	close(pipe_fd[0]);
	close(fds[1]);
	handle_child(argv[2], fds[0], pipe_fd[1], envp);
}

static void	handle_second_child(int *pipe_fd, int *fds, \
char **argv, char **envp)
{
	if (fds[1] < 0)
		fds[1] = open("/dev/null", O_WRONLY);
	close(pipe_fd[1]);
	close(fds[0]);
	handle_child(argv[3], pipe_fd[0], fds[1], envp);
}

static int	handle_exit_status(int *fds, int status2)
{
	int	exit_code;

	if (WIFEXITED(status2))
	{
		exit_code = WEXITSTATUS(status2);
		if (fds[1] < 0)
		{
			return (EXIT_FAILURE);
		}
		return (exit_code);
	}
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		fds[2];
	int		status1;
	int		status2;
	t_pid	pids;

	check_args(argc, argv);  // Updated to pass argv as well
	setup_files_and_pipe(pipe_fd, fds, argv);
	pids.pid1 = fork_child();
	if (pids.pid1 == 0)
	{
		handle_first_child(pipe_fd, fds, argv, envp);
	}
	pids.pid2 = fork_child();
	if (pids.pid2 == 0)
	{
		handle_second_child(pipe_fd, fds, argv, envp);
	}
	close_all_fds(pipe_fd, fds[0], fds[1]);
	waitpid(pids.pid1, &status1, 0);
	waitpid(pids.pid2, &status2, 0);
	return (handle_exit_status(fds, status2));
}

