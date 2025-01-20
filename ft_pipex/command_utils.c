/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:34:03 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/20 17:34:05 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path_var(char **envp)
{
	int		i;
	char	*path_var;

	i = 0;
	path_var = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path_var = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_var);
}

static char	*try_paths(char **paths, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		cmd_path = join_paths(paths[i], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*get_env_path(char **envp, char *cmd)
{
	char	*path_var;
	char	**paths;

	path_var = find_path_var(envp);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	return (try_paths(paths, cmd));
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
