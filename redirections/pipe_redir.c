/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:07:11 by ferenc            #+#    #+#             */
/*   Updated: 2025/05/26 12:21:47 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	handle_first_redir_child(t_shell *shell, t_shell *px, char *cmd)
{
	if (shell->redir_in != -1)
	{
		if (dup2(shell->redir_in, STDIN_FILENO) == -1)
			pipex_error("dup2 redir_in");
		close(shell->redir_in);
	}
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 pipe out");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
}

void	handle_last_redir_child(t_shell *shell, t_shell *px, char *cmd)
{
	if (dup2(px->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 pipe in");
	if (shell->redir_out != -1)
	{
		if (dup2(shell->redir_out, STDOUT_FILENO) == -1)
			pipex_error("dup2 redir_out");
		close(shell->redir_out);
	}
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
}

void	strip_redirection_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*next;

	tmp = *tokens;
	prev = NULL;
	while (tmp)
	{
		if (is_redir(tmp->com) && tmp->next)
		{
			next = tmp->next->next;
			if (prev)
				prev->next = next;
			else
				*tokens = next;
			tmp = next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	pipe_cmds_with_redir(char *command, t_token **tokens, t_shell *shell)
{
	t_shell	px;
	char	**cmds;
	int		cmd_count;
	char	**args;
	(void)command; //command is unused

	args = parse_args_and_redirs(*tokens, shell);
	strip_redirection_tokens(tokens);
	cmds = make_args_pipes(*tokens);
	if (!cmds)
		return ;
	cmd_count = cmd_counter(cmds);
	init_pipex(&px, shell);
	execute_piped_commands(&px, cmds, cmd_count, shell);
	free_array(cmds);
	free_array(args);
	reset_redirection(shell);
}
