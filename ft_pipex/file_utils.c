#include "pipex.h"

int	open_files(char *infile, char *outfile, int *infile_fd, int *outfile_fd)
{
	*infile_fd = open(infile, O_RDONLY);
	if (*infile_fd < 0)
	{
		if (errno == ENOENT)
			ft_printf("pipex: %s: No such file or directory\n", infile);
		else if (errno == EACCES)
			ft_printf("pipex: %s: Permission denied\n", infile);
		else
			perror("Error opening input file");
		return (-1);
	}
	*outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile_fd < 0)
	{
		if (errno == EACCES)
			ft_printf("pipex: %s: Permission denied\n", outfile);
		else
			perror("Error opening output file");
		close(*infile_fd);
		return (-1);
	}
	return (0);
}

void	setup_pipes(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		exit_with_error(ERR_PIPE);
	}
	ft_printf("Pipe created: pipe_fd[0]=%d \
    , pipe_fd[1]=%d\n", pipe_fd[0], pipe_fd[1]);
}

// join_paths: Joins two paths with a '/' separator.
char	*join_paths(char *path, char *cmd)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(path);
	len2 = ft_strlen(cmd);
	joined = malloc(len1 + len2 + 2);
	if (!joined)
		return (NULL);
	ft_strncpy(joined, path, len1);
	joined[len1] = '/';
	ft_strncpy(joined + len1 + 1, cmd, len2);
	joined[len1 + len2 + 1] = '\0';
	return (joined);
}
