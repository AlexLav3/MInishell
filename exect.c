/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/06 15:39:26 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//array creation
char	*make_args(t_token *tokens)
{
	char *cmd; 
	int i = 0; 
	int len = 0;
	while(tokens)
	{
		if(tokens->com)
		{
			len = ft_strlen(tokens->com);
			add_to_array(cmd,len, tokens->com);
		}		
		tokens = tokens->next;
	}
	return cmd;
}

void	add_to_array(char *cmd, int len, char *token)
{
	int i = 0;
	int k = 0; 
	cmd = malloc((sizeof(char*) * len) + 1);
	while(cmd[i])
		i++;
	while(token[k])
	{
		cmd[i] = token[k];
		i++;
		k++;
	}
}
