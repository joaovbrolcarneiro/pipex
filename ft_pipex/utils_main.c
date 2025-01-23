/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:16:48 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/23 15:03:55 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_usage(int argc)
{
	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
		exit(EXIT_FAILURE);
	}
}

static int	check_input_file(char *file)
{
	if (access(file, F_OK) == -1)
	{
		ft_printf("pipex: no such file or directory: %s\n", file);
		return (-1);
	}
	if (access(file, R_OK) == -1)
	{
		ft_printf("pipex: permission denied: %s\n", file);
		return (-1);
	}
	return (0);
}

static int	check_output_file(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("pipex: permission denied: %s\n", file);
		return (-1);
	}
	close(fd);
	if (access(file, F_OK) == -1)
	{
		ft_printf("pipex: no such file or directory: %s\n", file);
		return (-1);
	}
	if (access(file, W_OK) == -1)
	{
		ft_printf("pipex: permission denied: %s\n", file);
		return (-1);
	}
	return (0);
}

void	check_args(int argc, char **argv)
{
	check_usage(argc);
	if (check_input_file(argv[1]) == -1)
		return ;
	if (check_output_file(argv[4]) == -1)
		return ;
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
