/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/22 17:56:56 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	input(char *str, t_token **tokens)
{
	int		i;
	char	*word;
	int		word_len;
	int		start;

	i = 0;
	start = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (is_meta(str[i]) || str[i] == '"')
			i = make_tok(tokens, str, i);
		else
		{
			start = i;
			while (str[i] && str[i] != ' ' && !is_meta(str[i]) && str[i] != '"'
				&& str[i] != '\'')
				i++;
			word = ft_substr(str, start, i - start);
			add_token(tokens, word);
		}
		i++;
	}
	//print_list(*tokens);
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

int		make_tok(t_token **tokens, char *str, int i)
{
	char	*word;
	int		start;

	start = i;
	if (is_meta(str[i]))
	{
		while (str[i] && is_meta(str[i]))
			i++;
	}
	else if (str[i] == '"')
	{
		while (str[i] && str[i] != '"')
			i++;
	}
	word = ft_substr(str, start, i - start);
	add_token(tokens, word);
	return i;
}
