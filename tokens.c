/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:20:08 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/18 13:57:21 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_token	*new_token(char *word, int quoted)
{
	t_token	*tokens;
	static int created_tokens = 0; // update

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
	created_tokens++; // update
	return (tokens);
}

void add_token(t_token **head, char *word, int quoted)
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
