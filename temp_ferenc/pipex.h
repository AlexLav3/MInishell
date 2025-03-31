/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:48:48 by ferenc            #+#    #+#             */
/*   Updated: 2025/02/12 15:48:50 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**av;
	char	**envp;
}	t_pipex;

void	pipex_error(char *message);
void	execute_cmd(char *cmd, char **envp);
int		create_pipex(char **av, char **envp);
char	*join_path(const char *dir, const char *cmd);
void	free_array(char **arr);
char	*get_cmd_path(char *cmd, char **envp);
void	first_child_process(t_pipex *px);
void	second_child_process(t_pipex *px);
int		open_files(t_pipex *px);
void	close_pipes_and_wait(t_pipex *px);

#endif