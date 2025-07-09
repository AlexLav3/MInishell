/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 07:46:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/09 11:05:06 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	size_args(t_token *tokens)
{
	t_token	*tmp;
	int		count;

	count = 0;
	if (tokens == NULL)
		return (0);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->com && tmp->com[0] != '\0')
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	size_cmd_arg(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (!is_redir(tokens->com))
			count++;
		else if (tokens->next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}
