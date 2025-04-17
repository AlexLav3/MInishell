/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/17 14:37:00 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

		// if (is_sep(str[i]))
		// 	break ;
void	input(char *str, t_token **tokens)
{
	int		i;
	char	*word;
	int		start;
	int		word_len;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '"')
			i++;
		start = i;
		while (str[i] && str[i] != ' ' && str[i] != '"') // && !is_sep(str[i])
			i++;
		word_len = i - start;
		if (word_len > 0)
		{
			word = malloc(word_len + 1);
			if (!word)
				return ;
			ft_strlcpy(word, &str[start], word_len + 1);
			add_token(tokens, word);
		}
	}
	split_tokens(tokens);
}

t_token	*new_token(char *word)
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
	free(word);
	tokens->next = NULL;
	return (tokens);
}

void	add_token(t_token **head, char *word)
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
}
