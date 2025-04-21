/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 03:19:11 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/21 17:42:09 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == ';');
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

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
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

int	size_args(t_token *tokens)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = tokens;
	if (tokens == NULL)
		return (0);
	while (tmp)
	{
		if (tmp->com && !is_meta(tmp->com[0]))
			count++;
		tmp = tmp->next;
	}
	return (count);
}
