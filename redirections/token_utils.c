/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:50:10 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/19 21:16:28 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
 * Utility to check if a given string is a redirection symbol
 * such as "<", ">", ">>", or "<<".
 */
int	is_redir(const char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0 || \
			ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
}

/*
 * Checks a token list to see if it includes any redirection operators.
 * Skips NULL `com` (empty) fields and returns 1 if any redirection is found.
 */
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

void	cleanup_child_and_exit(t_cmd *cmd, t_shell *shell, t_token **tokens,
		int status)
{
	if (tokens)
		deallocate(tokens);
	if (cmd)
		reset_redirection(cmd);
	if (shell)
	{
		if (shell->env_var)
			free_array(shell->env_var);
		if (shell->pwd)
			free(shell->pwd);
		if (shell->infile)
			free(shell->infile);
		if (shell->outfile)
			free(shell->outfile);
	}
	exit(status);
}
