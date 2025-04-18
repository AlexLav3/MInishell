/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/16 15:06:08 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//array creation
char	**make_args(t_token *tokens)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		if (tokens->com && tokens->com[0] != '\0')
		{
			cmd[i] = ft_strdup(tokens->com);
			if (!cmd[i])
			{
				while (i > 0)
					free(cmd[--i]);
				return (free(cmd), NULL);
			}
			i++;
		}
		tokens = tokens->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
// tokens->com != NULL && !is_sep(tokens->com[0])
//why?
// we handle pipes and other sep before
