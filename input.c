/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/24 22:43:35 by elavrich         ###   ########.fr       */
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
			add_token(tokens, word, 0);
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
	int		start;
	char	*chunk;
	char	*builder;
	int		literal_only;

	literal_only = 0;
	builder = ft_strdup("");
	start = i;
	while (str[i] && str[i] != ' ' && !is_meta(str[i]))
	{
		if (str[i] == '\'')
		{
			literal_only = 1;
			start = ++i;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (printf("Unclosed single quote\n"), -1);
			chunk = ft_substr(str, start, i - start);
			builder = join_and_free(builder, chunk);
			i++;
		}
		else if (str[i] == '"')
		{
			start = ++i;
			while (str[i] && str[i] != '"') && !is_meta(str[i])
				i++;
			if (!str[i])
				return (printf("Unclosed double quote\n"), -1);
			chunk = ft_substr(str, start, i - start);
			builder = join_and_free(builder, chunk);
			i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != ' ' && !is_meta(str[i]) && str[i] != '\''
				&& str[i] != '"')
				i++;
			chunk = ft_substr(str, start, i - start);
			builder = join_and_free(builder, chunk);
		}
	}
	add_token(tokens, builder, literal_only);
	return (i);
}

//	TO RE-DO WITH NEW IMPLEMENTATION
// int	handle_single_q(t_token **tokens, char *str, int i)
// {
//
// 	return (i);
// }

// int	simple_word(t_token **tokens, char *str, int i)
// {
//
// 	return (i);
// }

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}
