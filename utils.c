/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 03:19:11 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 08:25:54 by elavrich         ###   ########.fr       */
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
