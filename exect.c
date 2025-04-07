/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/07 13:39:14 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//array creation
char	**make_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;
	char	**cmd;
	int		i;

	count = 0;
	i = 0;
	if (tokens == NULL)
		return (NULL);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->com && !is_sep(tmp->com[0]))
			count++;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->com && !is_sep(tmp->com[0]))
		{
			cmd[i] = ft_strdup(tmp->com);
			if (!cmd[i]) // f:07/04/25 - due to malloc, free the previous allocations as well
			{
				while (i > 0)
					free(cmd[--i]);
				free(cmd);
				return (NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
