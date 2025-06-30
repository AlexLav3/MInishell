#include <../Minishell.h>

static void	setup_in_out(t_shell *px, t_cmd *cmds, int cmd_count, int i)
{
	// Setup input
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
	// Setup output
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

void	execute_piped_commands(t_shell *px, t_cmd *cmds,
			int cmd_count, t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(px->pipe_fd) == -1)
			pipex_error("pipe failed");
		px->pid = fork();
		if (px->pid == -1)
			pipex_error("fork failed");
		if (px->pid == 0) // child
		{
			setup_in_out(px, cmds, cmd_count, i);
			close_all_pipe_fds(px);
			execve_cmd(&cmds[i], shell);
			exit(127);
		}
		update_fds(px);
	}
	close_pipes_and_wait(px);
}
void	single_cmd_with_redir(char *command, t_token **tokens, t_shell *shell)
{
	t_cmd	cmd;

	init_cmd(&cmd);
	cmd.args = parse_args_and_redirs(*tokens, &cmd, shell);
	free(command);
	if (!cmd.args || !cmd.args[0] || cmd.redir_error)
	{
		if (cmd.args)
			free_array(cmd.args);
		reset_redirection(&cmd); // update 27 jun
		return ;
	}
	execute_single_redir(&cmd, shell);
	free_array(cmd.args);
	reset_redirection(&cmd);
}

void	execute_single_redir(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	int		status;

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
		run_child_redir(path, cmd, shell);
	waitpid(shell->pid1, &status, 0);
	handle_exit_status(shell, status);
	if (path && path != cmd->args[0])
		free(path);
}