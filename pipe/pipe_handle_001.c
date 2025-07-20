/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle_001.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:33:46 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/20 08:29:55 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
 * Simple error handler that prints a message using `perror`
 * and exits the program with failure.
 */
void	pipex_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
 * Manages closing pipe file descriptors after forking a child.
 * Closes read end from previous command and write end of current pipe.
 * Prepares `prev_fd` for the next command in the chain.
 */
void	fd_handle(int i, int cmd_count, t_shell *px)
{
	if (i > 0 && px->prev_fd[0] >= 0)
		close(px->prev_fd[0]);
	if (i < cmd_count - 1 && px->pipe_fd[1] >= 0)
		close(px->pipe_fd[1]);
	if (i < cmd_count - 1)
		px->prev_fd[0] = px->pipe_fd[0];
}

/*
 * Decides which child function to run based on position in pipeline:
 * first, middle, or last. Also closes unused FDs in each child.
 */
void	which_child(int i, int cmd_count, t_shell *px, t_info *info)
{
	if (i == 0)
		first_child_process(px, info->cmd, info->tokens, info->cmds);
	else if (i == cmd_count - 1)
		last_child_process(px, info->cmd, info->tokens, info->cmds);
	else
		middle_child_process(px, info->cmd, info->tokens, info->cmds);
	if (i > 0)
		close(px->prev_fd[0]);
	if (i < cmd_count - 1)
		close(px->pipe_fd[1]);
}

static t_info	build_info(char *cmd, char **cmds, t_token **tokens)
{
	t_info	info;

	info.cmd = cmd;
	info.cmds = cmds;
	info.tokens = tokens;
	return (info);
}

/*
 * Main function to execute a sequence of piped commands.
 * Iterates through commands, sets up pipes and forks children.
 * Each child handles one command. Parent closes FDs and waits.
 */
void	create_pipes(char **cmds, t_shell *shell, t_token **tokens)
{
	int		i;
	int		cmd_count;
	t_shell	px;
	t_info	info;

	i = -1;
	init_pipex(&px, shell);
	cmd_count = size_cmd_arg(cmds);
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
			info = build_info(cmds[i], cmds, tokens);
			which_child(i, cmd_count, &px, &info);
			exit(0);
		}
		fd_handle(i, cmd_count, &px);
	}
	close_pipes_and_wait(&px, cmd_count);
}
