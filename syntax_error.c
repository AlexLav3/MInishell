/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:09:56 by ferenc            #+#    #+#             */
/*   Updated: 2025/07/09 20:30:09 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//syntax_error.c
static int	syntax_pipe(t_token *tokens)
{
	if (!tokens || !tokens->com)
		return (0);
	if (tokens->com[0] && is_pipe(tokens->com[0]) && !tokens->quoted)
	{
		printf("*** Syntax error: Missing Command before |. ***\n");
		return (1);
	}
	while (tokens)
	{
		if (tokens->com && is_pipe(tokens->com[0]) && !tokens->quoted)
		{
			if (!tokens->next || is_meta(tokens->next->com[0])
				|| (tokens->com[1] && is_pipe(tokens->com[1])))
			{
				printf("*** Syntax error: Missing Command after |. ***\n");
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	syntax_redir(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->com
			&& (tokens->com[0] == '>' || tokens->com[0] == '<')
			&& tokens->quoted == 0)
		{
			if (tokens->com[1]
				&& (tokens->com[1] == '>' || tokens->com[1] == '<')
				&& tokens->com[2]
				&& (tokens->com[2] == '>' || tokens->com[2] == '<'))
			{
				printf("*** Syntax error: Multiple Redirection. ***\n");
				return (4);
			}
			if (!tokens->next || is_meta(tokens->next->com[0]))
			{
				printf("*** Syntax error: Missing Target ***\n");
				return (4);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int	syntax_error(t_token **tokens)
{
	int	len;

	len = 0;
	if (len == 0)
		len = syntax_pipe(*tokens);
	if (len == 0)
		len = syntax_redir(*tokens);
	if (len > 0)
		deallocate(tokens);
	return (len);
}
