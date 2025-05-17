/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:29:16 by ferenc            #+#    #+#             */
/*   Updated: 2025/05/17 08:25:13 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	single_cmd(char *command, t_token **tokens, t_shell *shell)
{
	char	**cmd;

	cmd = make_args(*tokens, shell);
	free(command);
	if (!cmd)
	{
		deallocate(tokens);
		return ;
	}
	if (handle_builtin(cmd, shell))
	{
		free_array(cmd);
		deallocate(tokens);
		return ;
	}
	execute_single_cmd(cmd, shell);
	free_array(cmd);
}

void	pipe_cmds(char *command, t_token **tokens, t_shell *shell)
{
	char	**cmds;

	cmds = make_args_pipes(*tokens);
	free(command);
	if (!cmds)
	{
		deallocate(tokens);
		return ;
	}
	create_pipes(cmds, shell);
	free_array(cmds);
}

void	process_commands(char *command, t_token **tokens, t_shell *shell)
{
	int	has_pipe;
	int	has_redir;

	has_pipe = token_has_pipe(*tokens);
	has_redir = token_has_redir(*tokens);
	if (!has_pipe)
	{
		if (has_redir)
			single_cmd_with_redir(command, tokens, shell);
		else
			single_cmd(command, tokens, shell);
	}
	else
	{
		if (has_redir)
			pipe_cmds_with_redir(command, tokens, shell);
		else
			pipe_cmds(command, tokens, shell);
	}
	deallocate(tokens);
}
