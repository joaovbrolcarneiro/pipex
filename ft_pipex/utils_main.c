/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:16:48 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/21 18:16:49 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all_fds(int *pipe_fd, int infile_fd, int outfile_fd)
{
	close(infile_fd);
	close(outfile_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	check_args(int argc)
{
	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
		exit(EXIT_FAILURE);
	}
}

char	*strdup_until(const char *start, const char *end)
{
	size_t	len;
	char	*str;
	size_t	i;

	len = end - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = start[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

void	setup_files_and_pipe(int *pipe_fd, int *fds, char **argv)
{
	if (pipe(pipe_fd) == -1)
		exit_with_error("pipe");
	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] < 0)
		perror(argv[4]);
}
