/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:52:44 by ferenc            #+#    #+#             */
/*   Updated: 2025/02/12 15:52:47 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child_process(t_pipex *px)
{
	if (dup2(px->input_fd, 0) == -1 || dup2(px->pipe_fd[1], 1) == -1)
		pipex_error("Dup2 failed for cmd1");
	close(px->input_fd);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(px->av[2], px->envp);
}

void	second_child_process(t_pipex *px)
{
	if (dup2(px->pipe_fd[0], 0) == -1 || dup2(px->output_fd, 1) == -1)
		pipex_error("Dup2 failed for cmd2");
	close(px->output_fd);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(px->av[3], px->envp);
}

int	open_files(t_pipex *px)
{
	px->input_fd = open(px->av[1], O_RDONLY);
	if (px->input_fd == -1)
		px->input_fd = open("/dev/null", O_RDONLY, 0777);
	px->output_fd = open(px->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (px->output_fd == -1)
		return (pipex_error("Error opening output file"), -1);
	return (0);
}

void	close_pipes_and_wait(t_pipex *px)
{
	close(px->input_fd);
	close(px->output_fd);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	waitpid(px->pid1, NULL, 0);
	waitpid(px->pid2, NULL, 0);
}
