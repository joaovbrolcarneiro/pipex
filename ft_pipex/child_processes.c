/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:33:57 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/20 17:33:59 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_redirections(int fd_in, int fd_out)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 failed on input");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed on output");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
	close(fd_out);
}

static void	check_command_args(char **args)
{
	if (ft_strncmp(args[0], "grep", 5) == 0 && args[1] == NULL)
	{
		ft_printf("grep: missing argument to `-e'\n");
		free(args);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(args[0], "awk", 4) == 0 && args[1] == NULL)
	{
		ft_printf("awk: missing argument to pattern\n");
		free(args);
		exit(EXIT_FAILURE);
	}
}

static void	check_sed_options(char **args)
{
	if (ft_strncmp(args[0], "sed", 4) == 0)
	{
		if (args[1] && args[1][0] == '-' && args[1][1] != 'e')
		{
			ft_printf("sed: invalid option -- %c\n", args[1][1]);
			ft_printf("sed: usage: sed [-ne] [file ...]\n");
			free(args);
			exit(EXIT_FAILURE);
		}
	}
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
		exit_with_error(ERR_MALLOC);
	cmd_path = get_env_path(envp, args[0]);
	if (!cmd_path)
	{
		ft_printf("pipex: %s: command not found\n", args[0]);
		free(args);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		if (errno == EACCES)
			ft_printf("pipex: %s: Permission denied\n", args[0]);
		else
			ft_printf("pipex: %s: %s\n", args[0], strerror(errno));
		free(args);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}

void	handle_child(char *cmd, int fd_in, int fd_out, char **envp)
{
	char	**args;
	char	*cmd_path;

	handle_redirections(fd_in, fd_out);
	args = ft_split(cmd, ' ');
	if (!args)
		exit_with_error(ERR_MALLOC);
	cmd_path = get_env_path(envp, args[0]);
	if (!cmd_path)
	{
		ft_printf("pipex: %s: command not found\n", args[0]);
		free(args);
		exit(EXIT_FAILURE);
	}
	check_command_args(args);
	check_sed_options(args);
	free(args);
	execute_command(cmd, envp);
}
