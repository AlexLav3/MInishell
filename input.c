/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 09:00:03 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	input(char *str, t_token **tokens)
{
	int		i;
	char	*word;
	int		word_len;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\'')
		{
			i = handle_single_q(tokens, str, i);
			if (i < 0)
				break ;
		}
		else if (is_meta(str[i]) || str[i] == '"')
		{
			i = make_tok(tokens, str, i);
			if (i < 0)
				break ;
		}
		else
			i = simple_word(tokens, str, i);
	}
	return (i);
}

int	make_tok(t_token **tokens, char *str, int i)
{
	int		start;
	char	*word;

	start = i;
	if (str[i] == '"')
	{
		start = ++i;
		while (str[i] && str[i] != '"')
			i++;
		if (str[i] == '\0')
			return (printf("double quote missing\n"), -1);
		word = ft_substr(str, start, i - start);
		add_token(tokens, word, 0);
	}
	else if (is_meta(str[i]))
	{
		while (str[i] && is_meta(str[i]))
			i++;
		word = ft_substr(str, start, i - start);
		add_token(tokens, word, 0);
	}
	return (++i);
}

int	handle_single_q(t_token **tokens, char *str, int i)
{
	int		start;
	char	*word;

	start = ++i;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\0')
		return (printf("single quote missing\n"), -1);
	word = ft_substr(str, start, i - start);
	//printf("word: %s\n", word);
	if(word)
		add_token(tokens, word, 1);
	i++;
	return (i);
}
