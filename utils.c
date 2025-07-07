/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 03:19:11 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/07 13:40:58 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_pipe(char c)
{
	return (c == '|');
}

void	print_list(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->com)
			printf("token: %s\n", tokens->com);
		tokens = tokens->next;
	}
}

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}
