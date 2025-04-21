/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle_001.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:08:02 by ferenc            #+#    #+#             */
/*   Updated: 2025/04/16 15:17:30 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	pipex_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	cmd_counter(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	fd_handle(int i, int cmd_count, t_shell *px)
{
	if (i > 0)
		close(px->prev_fd[0]);
	if (i < cmd_count - 1)
		close(px->pipe_fd[1]);
	if (i < cmd_count - 1)
		px->prev_fd[0] = px->pipe_fd[0];
}

void	which_child(int i, int cmd_count, t_shell *px, char **cmds)
{
	if (i == 0)
		first_child_process(px, cmds[i]);
	else if (i == cmd_count - 1)
		last_child_process(px, cmds[i]);
	else
		middle_child_process(px, cmds[i]);
	if (i > 0)
		close(px->prev_fd[0]);
	if (i < cmd_count - 1)
		close(px->pipe_fd[1]);
}

void	create_pipes(char **cmds, t_shell *shell)
{
	int		i;
	int		cmd_count;
	t_shell	px;

	px.envp = shell->env_var;
	i = -1;
	px.pipe_fd[0] = -1;
	px.pipe_fd[1] = -1;
	cmd_count = cmd_counter(cmds);
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1)
			if (pipe(px.pipe_fd) == -1)
				pipex_error("Error creating pipe");
		px.pid = fork();
		if (px.pid == -1)
			pipex_error("Fork failed");
		if (px.pid == 0)
		{
			which_child(i, cmd_count, &px, cmds);
			exit(0);
		}
		fd_handle(i, cmd_count, &px);
	}
	close_pipes_and_wait(&px);
}
