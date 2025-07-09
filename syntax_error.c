/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:09:56 by ferenc            #+#    #+#             */
/*   Updated: 2025/07/09 14:10:23 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//syntax_error.c
int	is_in_quotes(char *command, char sign)
{
	int	i;
	char quote;
	
	quote = 0;
	i = 0;
	while (command[i])
	{
		if ((command[i] == '"' || command[i] == '\'') && quote == 0)
			quote = command[i];
		else if (command[i] == quote)
			quote = 0;
		else if (command[i] == sign && quote != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	syntax_pipe(t_token *tokens, char *command)
{
	if (!tokens || !tokens->com)
		return (0); 
	if (tokens->com[0] && is_pipe(tokens->com[0]))
	{
		printf("*** Syntax error: Missing Command before |. ***\n");
		return (1);
	}
	while (tokens)
	{
		if (tokens->com && is_pipe(tokens->com[0])
			&& !is_in_quotes(command, '|'))
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

static int	syntax_redir(t_token *tokens, char *command)
{
	while (tokens)
	{
		if (tokens->com
			&& (tokens->com[0] == '>' || tokens->com[0] == '<')
			&& (tokens->com[1] == '>' || tokens->com[1] == '<')
			&& (tokens->com[2] == '>' || tokens->com[2] == '<')
			&& (!is_in_quotes(command, '>') && !is_in_quotes(command, '<')))
		{
			printf("*** Syntax error: Multiple Consecutive Redirection. ***\n");
			return (4);
		}
		if (tokens->com
			&& (tokens->com[0] == '>' || tokens->com[0] == '<')
			&& (!is_in_quotes(command, '>') && !is_in_quotes(command, '<')))
		{
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

int	syntax_error(t_token **tokens, char *command)
{
	int	len;

	len = 0;
	if (len == 0)
		len = syntax_pipe(*tokens, command);
	if (len == 0)
		len = syntax_redir(*tokens, command);
	if (len > 0)
		deallocate(tokens);
	return (len);
}
