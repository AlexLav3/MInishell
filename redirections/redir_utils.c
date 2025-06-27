/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:55:44 by fnagy             #+#    #+#             */
/*   Updated: 2025/06/27 11:06:57 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// redir_utils.c
int	is_redir(const char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0 || \
	ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
}

int	token_has_redir(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->com)
		{
			tokens = tokens->next;
			continue ;
		}
		if (ft_strcmp(tokens->com, "<") == 0 || \
			ft_strcmp(tokens->com, ">") == 0 || \
			ft_strcmp(tokens->com, ">>") == 0 || \
			ft_strcmp(tokens->com, "<<") == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
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

void	reset_redirection(t_cmd *cmd)
{
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
	if (cmd->redir_in != -1)
	{
		close(cmd->redir_in);
		cmd->redir_in = -1;
	}
	if (cmd->redir_out != -1)
	{
		close(cmd->redir_out);
		cmd->redir_out = -1;
	}
}
