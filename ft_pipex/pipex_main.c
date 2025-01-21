/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:34:28 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/21 17:13:45 by jbrol-ca         ###   ########.fr       */
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

static void	check_args(int argc)
{
    if (argc != 5)
    {
        write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
        exit(EXIT_FAILURE);
    }
}

static void	setup_files_and_pipe(int *pipe_fd, int *fds, char **argv)
{
    if (pipe(pipe_fd) == -1)
        exit_with_error("pipe");
    fds[0] = open(argv[1], O_RDONLY);
    fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fds[1] < 0)
        perror(argv[4]);
}

static pid_t	fork_child(void)
{
    pid_t pid = fork();
    if (pid < 0)
        exit_with_error("fork");
    return pid;
}

static void	handle_child_process(int *pipe_fd, int *fds, char **argv, char **envp, int is_first)
{
    if (is_first)
    {
        if (fds[0] < 0)
            fds[0] = open("/dev/null", O_RDONLY);
        close(pipe_fd[0]);
        close(fds[1]);
        handle_child(argv[2], fds[0], pipe_fd[1], envp);
    }
    else
    {
        if (fds[1] < 0)
            fds[1] = open("/dev/null", O_WRONLY);
        close(pipe_fd[1]);
        close(fds[0]);
        handle_child(argv[3], pipe_fd[0], fds[1], envp);
    }
}

static int	handle_exit_status(int *fds, int status2)
{
    if (WIFEXITED(status2))
    {
        int exit_code = WEXITSTATUS(status2);
        if (fds[1] < 0)
            return EXIT_FAILURE;
        return exit_code;
    }
    return EXIT_FAILURE;
}

int	main(int argc, char **argv, char **envp)
{
    int pipe_fd[2], fds[2], status1, status2;
    pid_t pid1, pid2;

    check_args(argc);
    setup_files_and_pipe(pipe_fd, fds, argv);
    
    pid1 = fork_child();
    if (pid1 == 0)
        handle_child_process(pipe_fd, fds, argv, envp, 1);

    pid2 = fork_child();
    if (pid2 == 0)
        handle_child_process(pipe_fd, fds, argv, envp, 0);

    close_all_fds(pipe_fd, fds[0], fds[1]);
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    return handle_exit_status(fds, status2);
}
