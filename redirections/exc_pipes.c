/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:38:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/26 12:21:39 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	execute_single_redir(char **cmd, t_shell *shell)
{
	char	*path;

	if (!cmd[0] || !cmd)
		return ;
	path = get_cmd_path(cmd[0], shell);
	if (!path)
	{
		perror("Command not found utils.c redir");
		return ;
	}
	shell->pid1 = fork();
	if (shell->pid1 == -1)
		perror("fork utils.c redir");
	else if (shell->pid1 == 0)
	{
		apply_redirection(shell);
		if (execve(path, cmd, shell->env_var) == -1)
		{
			perror("execve failed utils.c redir");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(shell->pid1, NULL, 0); //we can use WEXITSTATUS for every waitpid, u ok if I add it?
	free(path);
}

void	execute_piped_commands(t_shell *px, char **cmds, int cmd_count, \
		t_shell *shell)
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
		if (px->pid == 0)
		{
			if (i == 0)
				handle_first_redir_child(shell, px, cmds[i]);
			else if (i == cmd_count - 1)
				handle_last_redir_child(shell, px, cmds[i]);
			else
				middle_child_process(px, cmds[i]);
			exit(0);
		}
		fd_handle(i, cmd_count, px);
	}
	close_pipes_and_wait(px);
}
