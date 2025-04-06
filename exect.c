/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/06 16:31:12 by elavrich         ###   ########.fr       */
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
	i = 0;
	while (tmp)
	{
		if (tmp->com && !is_sep(tmp->com[0]))
		{
			cmd[i] = ft_strdup(tmp->com);
			if (!cmd[i])
				return (NULL);
			i++;
		}
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
