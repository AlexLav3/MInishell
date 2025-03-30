/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 03:19:11 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/30 04:12:15 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	is_sep(char c)
{
	if (c == '<' || c == '$' || c == '|' || c == '-')
		return (1);
	else
		return (0);
}

void 	print_list(t_token *tokens)
{
	while(tokens)
	{ 
		if (tokens->com)
			printf("token value: %s\n", tokens->com);
		tokens = tokens->next;
	}
}
