/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:34:03 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/23 15:00:08 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_files_and_pipe(int *pipe_fd, int *fds, char **argv)
{
	if (pipe(pipe_fd) == -1)
		exit_with_error("pipe");
	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] < 0)
		perror(argv[4]);
}
