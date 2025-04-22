/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/22 17:59:08 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//array creation
//cat test.txt | grep "42" | sort | wc -l
char	**make_args(t_token *tokens)
{
	char	**cmd;
	int		i;

	i = 0;
	
	cmd = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmd || !tokens)
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

int ft_echo(char **cmd, t_shell *shell)
{
	
}
