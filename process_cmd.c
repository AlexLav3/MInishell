/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:29:16 by ferenc            #+#    #+#             */
/*   Updated: 2025/07/08 10:33:00 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	single_cmd(t_token **tokens, t_shell *shell)
{
	char	**cmd;

	cmd = make_args(*tokens, shell);
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

void	pipe_cmds(t_token **tokens, t_shell *shell)
{
	char	**cmds;

	cmds = make_args_pipes(*tokens);
	if (!cmds)
	{
		deallocate(tokens);
		return ;
	}
	create_pipes(cmds, shell);
	free_array(cmds);
}

void	process_commands(t_token **tokens, t_shell *shell)
{
	if (!token_has_pipe(*tokens))
	{
		if (token_has_redir(*tokens))
			single_cmd_with_redir(tokens, shell);
		else
			single_cmd(tokens, shell);
	}
	else
	{
		if (token_has_redir(*tokens))
			pipe_cmds_with_redir(tokens, shell);
		else
			pipe_cmds(tokens, shell);
	}
	deallocate(tokens);
}
