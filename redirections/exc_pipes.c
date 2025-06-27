/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:38:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/27 11:04:48 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// exc_pipes.c
void	execute_single_redir(t_cmd  *cmd, t_shell *shell)
{
	char	*path;
	int		status;

	status = 0;
	if (!cmd->args || !cmd->args[0] || cmd->redir_error)
		return ;
	path = get_cmd_path(cmd->args[0], shell);
	if (!path)
	{
		perror("Command not found utils.c redir");
		shell->exit_stat = 127;
		return ;
	}
	shell->pid1 = fork();
	if (shell->pid1 == -1)
	{
		perror("fork utils.c redir");
		shell->exit_stat = 1;
		if (path != cmd->args[0])
			free(path);
		return ;
	}
	else if (shell->pid1 == 0)
	{
		apply_redirection(cmd);
		execve(path, cmd->args, shell->env_var);
		perror("execve failed utils.c redir");
		shell->exit_stat = 127;
		exit(127); 
	}
	if (waitpid(shell->pid1, &status, 0) == -1)
	{
		perror("waitpid failed");
		shell->exit_stat = 1;
	}
	else if (WIFEXITED(status))
		shell->exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_stat = 128 + WTERMSIG(status);
	else
		shell->exit_stat = 1;
	if (path != cmd->args[0])
		free(path);
}

void	execute_piped_commands(t_shell *px, char **cmds, int cmd_count,
		t_shell *shell)
{
	int	i;
	t_token	*tokens;
	t_cmd	cmd;

	i = -1;
	while (++i < cmd_count)
	{
		init_cmd(&cmd);
		tokens = tokenize_command(cmds[i]);
		if (!tokens)
			exit(1); // temp
		cmd.args = parse_args_and_redirs(tokens, &cmd, shell);
		if (!cmd.args)
			exit(1); // temp
		strip_redirection_tokens(&tokens);
		if (i < cmd_count - 1 && pipe(px->pipe_fd) == -1)
			pipex_error("pipe failed");
		px->pid = fork();
		if (px->pid == -1)
			pipex_error("fork failed");
		if (px->pid == 0)
		{
			if (i == 0)
				handle_first_redir_child(&cmd, px, cmds[i]);
			else if (i == cmd_count - 1)
				handle_last_redir_child(&cmd, px, cmds[i]);
			else
				middle_child_process_redir(&cmd, px, cmds[i]);

			exit(0);
		}
		fd_handle(i, cmd_count, px);
		free_array(cmd.args);
		deallocate(&tokens);
		reset_redirection(&cmd);
	}
	close_pipes_and_wait(px);
}

