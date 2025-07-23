/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:39:00 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/23 17:03:19 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

static int	count_non_redir_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (token_is_redir(tokens))
		{
			tokens = tokens->next;
			if (tokens)
				tokens = tokens->next;
		}
		else
		{
			count++;
			tokens = tokens->next;
		}
	}
	return (count);
}

static bool	handle_redirs_only(t_token *delim, t_cmd *cmd, t_grouped group)
{
	t_token	*curr;

	curr = delim;
	while (curr)
	{
		if (token_is_redir(curr))
		{
			if (handle_redirection_token(&curr, cmd, group))
			{
				if (cmd->redir_error)
				{
					ft_putendl_fd("minishell: syntax error", 2);
					return (false);
				}
				curr = curr->next->next;
				continue ;
			}
		}
		curr = curr->next;
	}
	return (true);
}

static bool	fill_args_only(t_token *tokens, char **args, t_cmd *cmd)
{
	t_token	*curr;
	int		i;

	curr = tokens;
	i = 0;
	while (curr)
	{
		if (token_is_redir(curr))
		{
			curr = curr->next;
			if (curr)
				curr = curr->next;
			continue ;
		}
		if (handle_arg_token(&curr, args, &i) == -1)
		{
			free_partial_args(args, i);
			cmd->args = NULL;
			return (false);
		}
		i++;
		curr = curr->next;
	}
	args[i] = NULL;
	return (true);
}

/*
 * Parses the command's tokens into arguments and handles redirection
 * tokens (e.g. `<`, `>`, `>>`, `<<`). Returns the final arguments array.
 * Sets redirection fields in the `t_cmd` struct.
 */
char	**parse_args_and_redirs(t_token **tokens, t_cmd *cmd, t_grouped group)
{
	char	**args;
	int		arg_count;

	if (!handle_redirs_only(*tokens, cmd, group))
		return (NULL);
	arg_count = count_non_redir_tokens(*tokens);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
	{
		cleanup_heredoc_and_exit(cmd, group, 100);
		return (NULL);
	}
	if (!fill_args_only(*tokens, args, cmd))
		return (NULL);
	return (args);
}

/*
 * Checks the token type and handles redirection accordingly.
 * Delegates to appropriate functions for `<`, `>`, `>>`, or `<<`.
 * Returns 1 if it was a redirection token.
 */
int	handle_redirection_token(t_token **delim, t_cmd *cmd, t_grouped group)
{
	if (!delim || !*delim || !cmd || !group->shell || !group->tokens)
		return (0);
	if (cmd->redir_error)
		return (1);
	if ((*delim)->next == NULL)
		return (0);
	if (ft_strcmp((*delim)->com, "<") == 0 || ft_strcmp((*delim)->com,
			">") == 0)
		return (redir_token_in_out(delim, cmd));
	else if (ft_strcmp((*delim)->com, ">>") == 0)
		return (redir_token_append(delim, cmd));
	else if ((*delim)->com && ft_strcmp((*delim)->com, "<<") == 0)
	{
		if ((*delim)->next && (*delim)->next->com)
		{
			heredoc_do(cmd, group, (*delim)->next->com);
			return (1);
		}
		else
		{
			ft_putendl_fd("minishell: syntax error near `<<`", 2);
			return (cmd->redir_error = 1, 1);
		}
	}
	return (0);
}
