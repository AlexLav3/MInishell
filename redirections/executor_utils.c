/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:37:47 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/03 20:37:53 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

/*
 * Determines the shell's exit status based on how a child process
 * exited. Handles normal exits and signals (e.g. SIGINT, SIGQUIT).
 * Sets `exit_stat` accordingly for proper shell behavior.
 */
void	handle_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_stat = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
	}
	else
		shell->exit_stat = 1;
}

/*
 * Verifies that the command is valid and attempts to resolve its
 * executable path via `get_cmd_path`. Returns 0 on failure.
 * Sets `exit_stat` to 127 if command is not found.
 */
int	prep_command_path(t_cmd *cmd, t_shell *shell, char **path)
{
	if (!cmd->args || !cmd->args[0] || cmd->redir_error)
		return (0);
	*path = get_cmd_path(cmd->args[0], shell);
	if (!*path)
	{
		perror("Command not found utils.c redir");
		shell->exit_stat = 127;
		return (0);
	}
	return (1);
}

/*
 * Applies input/output redirection for a single command, then
 * uses `execve()` to execute it. If execution fails, exits with 127.
 */
void	run_child_redir(char *path, t_cmd *cmd, t_shell *shell)
{
	apply_redirection(cmd);
	execve(path, cmd->args, shell->env_var);
	perror("execve failed utils.c redir");
	exit(127);
}

/*
 * Used in piped execution.
 * Applies redirection, gets full command path,
 * then executes using `execve`. Frees resources and exits on failure.
 */
void	execve_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*full_path;

	apply_redirection(cmd);
	full_path = get_cmd_path(cmd->args[0], shell);
	if (!full_path)
	{
		perror(cmd->args[0]);
		exit(127);
	}
	execve(full_path, cmd->args, shell->env_var);
	perror("execve");
	free(full_path);
	exit(1);
}

/*
 * Safely closes all pipe file descriptors (`pipe_fd` and `prev_fd`)
 * in the current process to avoid leaks or interference.
 */
void	close_all_pipe_fds(t_shell *px)
{
	if (px->pipe_fd[0] >= 0)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] >= 0)
		close(px->pipe_fd[1]);
	if (px->prev_fd[0] >= 0)
		close(px->prev_fd[0]);
	if (px->prev_fd[1] >= 0)
		close(px->prev_fd[1]);
}
