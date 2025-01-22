/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:16:48 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/22 19:13:23 by jbrol-ca         ###   ########.fr       */
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

void	check_args(int argc, char **argv)
{
	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
		exit(EXIT_FAILURE);  // Exit immediately if arguments are incorrect
	}

	// Check if the input file exists
	if (access(argv[1], F_OK) == -1)  // File does not exist
	{
		ft_printf("pipex: no such file or directory: %s\n", argv[1]);
		return;  // Just return without exiting
	}

	// Check if the input file has read permissions
	if (access(argv[1], R_OK) == -1)  // File is not readable
	{
		ft_printf("pipex: permission denied: %s\n", argv[1]);
		return;  // Just return without exiting
	}

	// Check if the output file's directory exists (if needed)
	if (access(argv[4], F_OK) == -1)  // Directory does not exist
	{
		ft_printf("pipex: no such file or directory: %s\n", argv[4]);
		return;  // Just return without exiting
	}

	// Check if the output file has write permissions
	if (access(argv[4], W_OK) == -1)  // File is not writable
	{
		ft_printf("pipex: permission denied: %s\n", argv[4]);
		return;  // Just return without exiting
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
