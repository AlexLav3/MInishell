/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:20:08 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/26 12:27:43 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_token	*new_token(char *word)
{
	t_token	*tokens;

	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->com = ft_strdup(word);
	tokens->literal = false;
	if (!tokens->com)
	{
		free(word);
		return (free(tokens), NULL);
	}
	// free(word);
	tokens->next = NULL;
	return (tokens);
}

void	add_token(t_token **head, char *word, int literal)
{
	t_token	*new;
	t_token	*tmp;
	
	new = new_token(word);
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
	if (literal)
		new->literal = true;
	return ;
}
