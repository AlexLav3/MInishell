/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/25 21:28:00 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	input(char *str, t_token **tokens)
{
	int		i;
	char	*word;
	int		start;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (is_meta(str[i]))
		{
			start = i;
			while (str[i] && is_meta(str[i]))
				i++;
			word = ft_substr(str, start, i - start);
			add_token(tokens, word);
		}
		else
		{
			i = make_tok(tokens, str, i);
			if (i < 0)
				return (-1);
		}
	}
	return (i);
}

int	make_tok(t_token **tokens, char *str, int i)
{
	char		*chunk;
	char		*builder;
	t_token_b	*tks;

	tks = malloc(sizeof(t_token_b));
	tks->builder = ft_strdup("");
	while (str[i] && str[i] != ' ' && !is_meta(str[i]))
	{
		// if (str[i] == '\'' || str[i] == '"')
		// {
		// 	i = handle_q(&tks, str, i);
		// 	if (i < 0)
		// 		return (-1);
		// }
		// else
			i = simple_word(&tks, str, i);	
	}
	add_token(tokens, tks->builder);
	return (i);
}

int	handle_q(t_token_b **tks, char *str, int i)
{
	int	start;
	int tmp = i;
	start = ++i;
	if (str[tmp] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	else if (str[tmp] == '"')
	{
		while (str[i] && str[i] != '"')
			i++;
	}
	if (!str[i])
		return (printf("Unclosed quote\n"), -1);
	(*tks)->chunk = ft_substr(str, start, i - start);
	(*tks)->builder = join_and_free((*tks)->builder, (*tks)->chunk);
	i++;
	return (i);
}

int	simple_word(t_token_b **tks, char *str, int i)
{
	int	start;

	start = i;
	while (str[i] && str[i] != ' ' && !is_meta(str[i]))
		i++;
	(*tks)->chunk = ft_substr(str, start, i - start);
	(*tks)->builder = join_and_free((*tks)->builder, (*tks)->chunk);
	return (i);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}
