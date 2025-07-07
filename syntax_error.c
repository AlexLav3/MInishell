/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:09:56 by ferenc            #+#    #+#             */
/*   Updated: 2025/07/07 16:15:39 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//syntax_error.c
static int	is_special(char c)
{
	return (c != ';'
		&& c != '\\'
		&& c != '#'
		&& c != '!'
		&& c != '~'
		&& c != '&'
		&& c != '('
		&& c != ')'
		&& c != '['
		&& c != ']'
		&& c != '{'
		&& c != '}');
}

// *** Special characters are ignored. ***
// *** ; \\ # ! ~ & ( ) [ ] { } ***
void	strip_char(char *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!command)
		return ;
	while (command[i])
	{
		if (is_special(command[i]))
		{
			command[j] = command[i];
			j++;
		}
		i++;
	}
	command[j] = '\0';
}

static int	syntax_pipe(t_token *tokens)
{
	if (is_pipe(tokens->com[0]))
	{
		printf("*** Syntax error: Missing Command before |. ***\n");
		return (1);
	}
	while (tokens)
	{
		if (tokens->com && is_pipe(tokens->com[0]))
		{
			if (!tokens->next || is_meta(tokens->next->com[0])
				|| is_pipe(tokens->com[1]))
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
			&& (tokens->com[1] == '>' || tokens->com[1] == '<')
			&& (tokens->com[2] == '>' || tokens->com[2] == '<'))
		{
			printf("*** Syntax error: Multiple Consecutive Redirection. ***\n");
			return (4);
		}
		if (tokens->com
			&& (tokens->com[0] == '>' || tokens->com[0] == '<'))
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
