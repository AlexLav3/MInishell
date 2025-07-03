/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:50:10 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/03 21:07:54 by elavrich         ###   ########.fr       */
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

/*
 * Helper function that removes a redirection token and its associated argument
 * from the token list, adjusting pointers and freeing memory.
 * It removes **a single redirection token 
 * and its argument** from the linked list.
 * For example, given tokens: [ls] [>] [file.txt], 
 * it removes both ">" and "file.txt".
 */
// static void	remove_redir(t_token **tokens, t_token **curr, t_token **prev)
// {
// 	t_token	*to_free;
// 	t_token	*next_token;

// 	to_free = *curr;
// 	next_token = (*curr)->next;
// 	if (*prev)
// 		(*prev)->next = next_token->next;
// 	else
// 		*tokens = next_token->next;
// 	*curr = next_token->next;
// 	free(to_free->com);
// 	free(to_free);
// 	free(next_token->com);
// 	free(next_token);
// }
