/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle_002.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:34:09 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/20 18:27:43 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
 * Handles the first command in a pipeline.
 * Redirects STDOUT to pipe write end and executes the command.
 */
void	first_child_process(t_shell *px, char *cmd, t_token **tokens,
		char **cmds)
{
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 failed for first child");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px, tokens, cmds);
}

/*
 * Handles the last command in a pipeline.
 * Redirects STDIN from pipe read end and executes the command.
 */
void	last_child_process(t_shell *px, char *cmd, t_token **tokens,
		char **cmds)
{
	if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 failed for last child");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	close(px->prev_fd[0]);
	execute_cmd(cmd, px, tokens, cmds);
}

/*
 * Handles intermediate commands in a pipeline.
 * Redirects STDIN from previous pipe read end,
 * and STDOUT to current pipe write end, then executes.
 */
void	middle_child_process(t_shell *px, char *cmd, t_token **tokens,
		char **cmds)
{
	if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 failed for intermediate child (stdin)");
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 failed for intermediate child (stdout)");
	close(px->prev_fd[0]);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px, tokens, cmds);
}

/*
 * Closes all remaining pipe FDs in the parent process.
 * Waits for all child processes to finish using `wait`.
 */
void	close_pipes_and_wait(t_shell *px, int cmd_count)
{
	int		status;
	pid_t	pid;
	int		i;

	if (px->pipe_fd[0] != -1)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] != -1)
		close(px->pipe_fd[1]);
	if (px->prev_fd[0] != -1)
		close(px->prev_fd[0]);
	if (px->prev_fd[1] != -1)
		close(px->prev_fd[1]);
	i = 0;
	while (i < cmd_count)
	{
		pid = wait(&status);
		if (pid == -1)
			perror("wait");
		i++;
	}
}

/*
 * Parses a command string into args and searches for the binary path.
 * If found, executes the command with `execve`, else prints an error.
 */
void	execute_cmd(char *cmd, t_shell *px, t_token **tokens, char **cmds)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		pipex_error("split");
	if (handle_builtin(args, px))
	{
		cleanup(args, px, tokens, cmds);
		exit(0);
	}
	path = get_right_path(args[0], px, 1);
	if (!path)
	{
		write(STDERR_FILENO, args[0], ft_strlen(args[0]));
		write(STDERR_FILENO, ": command not found\n", 21);
		cleanup(args, px, tokens, cmds);
		exit(127);
	}
	if (execve(path, args, px->env_var) == -1)
	{
		pipex_error("execve");
		cleanup(args, px, tokens, cmds);
		exit(127);
	}
}
