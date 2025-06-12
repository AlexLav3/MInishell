/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:38:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/11 14:14:22 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
we can use WEXITSTATUS for every waitpid, u ok if I add it?
f: I do not know how that works. I think we need to keep waitpid and add WEXITSTATUS 
on top of that, which means extra lines. But feel free to try it. 

I know how it works, I'll do it. 
*/
void	execute_single_redir(char **cmd, t_shell *shell)
{
	char	*path;

	if (!cmd[0] || !cmd)
		return ;
	path = get_right_path(cmd[0], shell, 0);
	if (!path)
		return ((void)(perror("Command not found utils.c redir"), shell->exit_stat = 127));
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
    waitpid(shell->pid1, NULL, 0);
	if (path != cmd[0])
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
