/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:16:16 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/22 18:57:15 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* pipex.h */
#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "libft/inc/ft_printf.h"

# define ERR_CMD "command not found"
# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_FILE "File error"
# define ERR_MALLOC "Memory allocation error"

/* Struct for process IDs */
typedef struct s_pid
{
	pid_t	pid1;
	pid_t	pid2;
}	t_pid;

/* Function Prototypes */
void	exit_with_error(const char *message);
int		open_files(char *infile, char *outfile, \
int *infile_fd, int *outfile_fd);
void	setup_pipes(int pipe_fd[2]);
void	execute_command(char *cmd, char **envp);
void	handle_child(char *cmd, int fd_in, int fd_out, char **envp);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*join_paths(char *path, char *cmd);
char	*get_env_path(char **envp, char *cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strcpy(char *dest, const char *src);
void	free_array(char **arr);
char	*find_path(char *cmd, char **envp);
char	*strdup_until(const char *start, const char *end);
char	*ft_strncpy(char *dest, const char *src, size_t n);
void	free_args(char **args);
void	close_all_fds(int *pipe_fd, int infile_fd, int outfile_fd);
void	check_args(int argc, char **argv);
void	setup_files_and_pipe(int *pipe_fd, int *fds, char **argv);

#endif
