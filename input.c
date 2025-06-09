/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/30 15:08:04 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static int	handle_meta(char *str, t_token **tokens, int i)
{
	int		start;
	char	*word;

	start = i;
	while (str[i] && is_meta(str[i]))
		i++;
	word = ft_substr(str, start, i - start);
	if (!word)
		return (-1);
	add_token(tokens, word);
	free(word);
	return (i);
}

int	input(char *str, t_token **tokens, t_shell *shell)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (is_meta(str[i]))
			i = handle_meta(str, tokens, i);
		else
		{
			i = make_tok(tokens, str, i, shell);
			if (i < 0)
				return (-1);
		}
	}
	return (i);
}

int	make_tok(t_token **tokens, char *str, int i, t_shell *shell)
{
	t_token_b	*tks;

	tks = malloc(sizeof(t_token_b));
	if (!tks)
		return (-1);
	tks->builder = ft_strdup("");
	if (!tks->builder)
		return (free(tks), -1);
	while (str[i] && str[i] != ' ' && !is_meta(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = handle_q(&tks, str, i, shell);
			if (i < 0)
				return (free(tks->builder), free(tks), -1);
		}
		else
			i = simple_word(&tks, str, i, shell);
	}
	add_token(tokens, tks->builder);
	return (free(tks->builder), free(tks), i);
}

int	handle_q(t_token_b **tks, char *str, int i, t_shell *shell)
{
	int	start;
	int	tmp;

	tmp = i;
	int flag ;
	start = ++i;
	if (str[tmp] == '\'')
	{
		flag = NO_EXP;
		while (str[i] && str[i] != '\'')
			i++;
	}
	else if (str[tmp] == '"')
	{
		flag = EXPAND;
		while (str[i] && str[i] != '"')
			i++;
	}
	if (!str[i])
		return (printf("Unclosed quote\n"), -1);
	t_words *new_part = word_node(ft_substr(str, start, i - start), flag);
	append_word(&(*tks)->parts, new_part);
	t_words *last = (*tks)->parts;
	while (last->next)
		last = last->next;
	process_word(last, shell);
	(*tks)->builder = join_and_free((*tks)->builder, last->word);
	i++;
	return (i);
}

int	simple_word(t_token_b **tks, char *str, int i, t_shell *shell)
{
	int	start;

	start = i;
	while (str[i] && str[i] != ' ' && !is_meta(str[i]) && str[i] != '\''
		&& str[i] != '"')
		i++;
	t_words *new_part = word_node(ft_substr(str, start, i - start), EXPAND);
	append_word(&(*tks)->parts, new_part);
	printf("after expansion: %s\n", new_part->word);
	t_words *last = (*tks)->parts;
	process_word(new_part, shell);
	while (last->next)
    	last = last->next;
	(*tks)->builder = join_and_free((*tks)->builder, last->word);
	printf("tokens builder: %s\n", (*tks)->builder);
	return (i);
}