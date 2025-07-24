/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:09:56 by ferenc            #+#    #+#             */
/*   Updated: 2025/07/24 16:54:16 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static int	syntax_pipe(t_token *tokens, t_shell *shell)
{
	if (!tokens || !tokens->com)
		return (0);
	if (tokens->com[0] && is_pipe(tokens->com[0]) && !tokens->quoted)
	{
		printf("*** Syntax error: Missing Command before |. ***\n");
		shell->exit_stat = 127;
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
				shell->exit_stat = 127;
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	syntax_redir(t_token *tokens, t_shell *shell)
{
	while (tokens)
	{
		if (tokens->com && (tokens->com[0] == '>' || tokens->com[0] == '<')
			&& !tokens->quoted)
		{
			if (tokens->com[1] && (tokens->com[1] == '>'
					|| tokens->com[1] == '<') && tokens->com[2]
				&& (tokens->com[2] == '>' || tokens->com[2] == '<'))
			{
				printf("*** Syntax error: Multiple Redirection. ***\n");
				shell->exit_stat = 127;
				return (4);
			}
			if (!tokens->next || is_meta(tokens->next->com[0])
				|| tokens->com[1] == '|')
			{
				printf("*** Syntax error: Missing Target ***\n");
				shell->exit_stat = 127;
				return (4);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int	syntax_error(t_token **tokens, t_shell *shell)
{
	int	len;

	len = 0;
	if (len == 0)
		len = syntax_pipe(*tokens, shell);
	if (len == 0)
		len = syntax_redir(*tokens, shell);
	if (len > 0)
		deallocate(tokens);
	return (len);
}
