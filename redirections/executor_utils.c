#include <../Minishell.h>

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

void	run_child_redir(char *path, t_cmd *cmd, t_shell *shell)
{
	apply_redirection(cmd);
	execve(path, cmd->args, shell->env_var);
	perror("execve failed utils.c redir");
	exit(127);
}

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

// similar to close_pipes_and_wait, needs to rework
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