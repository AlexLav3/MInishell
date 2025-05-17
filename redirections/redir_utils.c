/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:55:44 by fnagy             #+#    #+#             */
/*   Updated: 2025/05/17 06:48:44 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	is_redir(const char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0 || \
	ft_strcmp(s, ">>") == 0);
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (!is_redir(tokens->com))
			count++;
		else if (tokens->next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
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
	char	**args;

	args = parse_args_and_redirs(*tokens, shell);
	free(command);
	if (!args || !args[0])
		return ;
	execute_single_redir(args, shell);
	free_array(args);
	reset_redirection(shell);
}

void	reset_redirection(t_shell *shell)
{
	if (shell->infile)
		free(shell->infile);
	if (shell->outfile)
		free(shell->outfile);
	shell->infile = NULL;
	shell->outfile = NULL;
	if (shell->redir_in != -1)
		close(shell->redir_in);
	if (shell->redir_out != -1)
		close(shell->redir_out);
	shell->redir_in = -1;
	shell->redir_out = -1;
}
