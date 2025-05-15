/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/16 00:15:05 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	input(char *str, t_token **tokens)
{
	int		i;
	char	*word;
	int		word_len;
	int		start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '\'')
			i = handle_single_q(tokens, str, i);
		else if (is_meta(str[i]) || str[i] == '"')
			i = make_tok(tokens, str, i);
		else
		{
			start = i;
			while (str[i] && str[i] != ' ' && !is_meta(str[i]) && str[i] != '"'
				&& str[i] != '\'')
					i++;
			word = ft_substr(str, start, i - start);
			add_token(tokens, word, 0);
		}
	}
	return (i);
}

t_token	*new_token(char *word)
{
	t_token	*tokens;

	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->com = ft_strdup(word);
	printf("tokens com: %s\n", tokens->com);
	tokens->literal = false;
	if (!tokens->com)
	{
		free(word);
		return (free(tokens), NULL);
	}
	free(word);
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
	if(literal)
		new->literal = true;
	return;
}

int	make_tok(t_token **tokens, char *str, int i)
{
	int		start;
	char	*word;

	start = i;
	if (is_meta(str[i]))
	{
		while (str[i] && is_meta(str[i]))
			i++;
	}
	else if (str[i] == '"')
	{
		start = ++i;
		while (str[i] && str[i] != '"')
			i++;
		if (str[i] == '\0')
			return (printf("quote missing\n"), i);
		word = ft_substr(str, start, i - start);
		if (word[0] == '\'' && word[ft_strlen(word) - 1] == '\'')
		{
			char *cleaned = ft_substr(word, 1, ft_strlen(word) - 2);
			add_token(tokens, cleaned, 0);
		}
		else
			add_token(tokens, word, 0);
		i++;
		return (i);
	}
	word = ft_substr(str, start, i - start);
	add_token(tokens, word, 0);
	return (i);
}

int	handle_single_q(t_token **tokens, char *str, int i)
{
	int		start;
	char	*word;
	
	start = ++i;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\0')
		return (printf("quote missing\n"), 0);
	word = ft_substr(str, start, i - start);
	add_token(tokens, word, 1);
	i++;
	return (i);
}
