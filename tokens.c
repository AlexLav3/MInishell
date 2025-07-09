/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:20:08 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/09 20:22:58 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_token	*new_token(char *word, int quoted)
{
	t_token	*tokens;

	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->com = ft_strdup(word);
	if (!tokens->com)
	{
		free(word);
		return (free(tokens), NULL);
	}
	tokens->next = NULL;
	tokens->quoted = quoted;
	return (tokens);
}

void	add_token(t_token **head, char *word, int quoted)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(word, quoted);
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ;
}
