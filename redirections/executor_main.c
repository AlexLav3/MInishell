/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:37:01 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/24 17:02:41 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

/* 
 * This function sets up the `stdin` and `stdout` of a child process
 * depending on the current command's redirection flags and its position
 * in the pipeline. It uses `dup2()` to redirect input/output from/to:
 * - Redirection file descriptors if present
 * - Previous pipe for input (if not the first command)
 * - Next pipe for output (if not the last command)
 */
static void	setup_in_out(t_shell *px, t_cmd *cmds, int cmd_count, int i)
{
	if (cmds[i].redir_in != -1)
	{
		if (dup2(cmds[i].redir_in, STDIN_FILENO) == -1)
			pipex_error("dup2 redir_in");
	}
	else if (i > 0)
	{
		if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
			pipex_error("dup2 prev_fd[0]");
	}
	if (cmds[i].redir_out != -1)
	{
		if (dup2(cmds[i].redir_out, STDOUT_FILENO) == -1)
			pipex_error("dup2 redir_out");
	}
	else if (i < cmd_count - 1)
	{
		if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
			pipex_error("dup2 pipe_fd[1]");
	}
}

/*
 * Closes the previous pipe file descriptors if open, then assigns the
 * current pipe's file descriptors to `prev_fd` in preparation for the
 * next iteration of piped execution.
 * This ensures correct chaining of pipes across multiple commands.
 */
static void	update_fds(t_shell *px)
{
	if (px->prev_fd[0] != -1)
		close(px->prev_fd[0]);
	if (px->prev_fd[1] != -1)
		close(px->prev_fd[1]);
	px->prev_fd[0] = px->pipe_fd[0];
	px->prev_fd[1] = px->pipe_fd[1];
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
}

/*
 * Forks and executes each command in the pipeline. For each command:
 * - Creates a pipe (unless it's the last one)
 * - Forks a child process
 * - Sets up redirections and pipe connections using `setup_in_out`
 * - Calls `execve_cmd()` in the child
 * - In the parent, updates pipe file descriptors
 * At the end, it waits for all child processes.
 */
void	execute_piped_commands(t_shell *px, t_grouped grp)
{
	int	i;

	i = -1;
	while (++i < grp->cmd_count)
	{
		if (i < grp->cmd_count - 1 && pipe(px->pipe_fd) == -1)
			pipex_error("pipe failed");
		px->pid = fork();
		if (px->pid == -1)
			pipex_error("fork failed");
		if (px->pid == 0)
		{
			setup_in_out(px, grp->cmds, grp->cmd_count, i);
			close_all_pipe_fds(px);
			execve_cmd(&grp->cmds[i], grp->shell, grp->tokens);
			exit(127);
		}
		update_fds(px);
	}
	close_pipes_and_wait(px, grp->cmd_count);
}

/*
 * Handles a single, non-piped command with potential redirections.
 * Parses arguments and redirection tokens, and if valid,
 * executes the command using `execute_single_redir()`.
 * Performs memory cleanup afterward.
 */
void	single_cmd_with_redir(t_token **tokens, t_shell *shell)
{
	t_cmd		cmd;
	t_grouped	group;

	init_cmd(&cmd);
	group = build_group(shell, &cmd, 1, tokens);
	if (!group)
		return ;
	cmd.args = parse_args_and_redirs(tokens, &cmd, group);
	if (!cmd.args || !cmd.args[0] || cmd.redir_error)
	{
		if (cmd.args)
			free_array(cmd.args);
		reset_redirection(&cmd);
		free(group);
		return ;
	}
	execute_single_redir(&cmd, shell, tokens);
	free_array(cmd.args);
	reset_redirection(&cmd);
	free(group);
}

/*
 * Executes a single command with redirection.
 * - Prepares the command path using `prep_command_path`
 * - Forks a child process
 * - In child: applies redirection and runs execve
 * - In parent: waits and handles the exit status
 * Frees the command path if necessary.
 */

void	execute_single_redir(t_cmd *cmd, t_shell *shell, t_token **tokens)
{
	char	*path;
	int		status;
	pid_t	ret;

	if (!prep_command_path(cmd, shell, &path))
		return ;
	shell->pid1 = fork();
	if (shell->pid1 == -1)
	{
		perror("fork utils.c redir");
		shell->exit_stat = 1;
		if (path != cmd->args[0])
			free(path);
		return ;
	}
	if (shell->pid1 == 0)
		run_child_redir(path, cmd, shell, tokens);
	ret = waitpid(shell->pid1, &status, 0);
	if (ret == -1)
		shell->exit_stat = 1;
	else
		handle_exit_status(shell, status);
	if (path && path != cmd->args[0])
		free(path);
}
