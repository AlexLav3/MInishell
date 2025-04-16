/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle_002.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:55:59 by ferenc            #+#    #+#             */
/*   Updated: 2025/04/16 15:22:42 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	first_child_process(t_shell *px, char *cmd)
{
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 failed for first child");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
}

void	last_child_process(t_shell *px, char *cmd)
{
	if (dup2(px->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 failed for last child");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
}

void	middle_child_process(t_shell *px, char *cmd)
{
	if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 failed for intermediate child (stdin)");
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 failed for intermediate child (stdout)");
	close(px->prev_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
	exit(0);
}

void	close_pipes_and_wait(t_shell *px)
{
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	while (wait(NULL) > 0)
		;
}

void	execute_cmd(char *cmd, t_shell *px)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		pipex_error("split");
	path = get_path_in(args[0], px);
	if (!path)
		pipex_error("command not found");
	if (execve(path, args, px->envp) == -1)
		pipex_error("execve");
}
