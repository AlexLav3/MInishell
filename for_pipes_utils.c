/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:53:39 by ferenc            #+#    #+#             */
/*   Updated: 2025/04/10 03:43:31 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	has_seps(char **cmd, char sep)
{
	int i;

	i = 0;
	while (cmd[i])
	{							//and if index one is the end? what is they are later?
		if (cmd[i][0] == sep && cmd[i][1] == '\0') // cmd {"ls", "|", "grep", "a", NULL}
			return (1);
		i++;
	}
	return (0);
}
// count how many pipes we have in the command line
int	count_seps(char **cmd, char sep)
{
	int i;
	int count;

	i = 0;
	count = 1;
	if (!cmd)
		return (0);
	while (cmd[i])
	{							//and if it's the end of string? why?
		if (cmd[i][0] == sep && cmd[i][1] == '\0')
			count++;
		i++;		
	}
	return (count);
}
// count how manny commands we have apart the pipes (before/after pipes)
int count_segment_tokens(char **cmd, int start, char sep)
{
	int count;
	
	count = 0;
	if (!cmd || start < 0)
		return 0;									//why and index one is the end of string? 
	while (cmd[start] && !(cmd[start][0] == sep && cmd[start][1] == '\0'))
	{
		count++;
		start++;
	}
	return (count);

}

void free_av(char ***av)
{
	int i;

	if (!av || !*av)
		return;

	i = 0;
	while ((*av)[i])
	{
		free((*av)[i]);
		i++;
	}
	free(*av);
	*av = NULL;
}
