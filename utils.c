/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 03:19:11 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 08:04:57 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

int	is_pipe(char c)
{
	return (c == '|');
}

void	print_list(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->com)
			printf("token value: %s\n", tokens->com);
		tokens = tokens->next;
	}
}

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

int	simple_word(t_token **tokens, char *str, int i)
{
	char	*word;
	int		start;

	start = i;
	while (str[i] && str[i] != ' ' && !is_meta(str[i]) && str[i] != '"'
		&& str[i] != '\'' && str[i] != '\0')
		i++;
	word = ft_substr(str, start, i - start);
	add_token(tokens, word, 0);
	return (i);
}
