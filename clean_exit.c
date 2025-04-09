/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:57 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/09 16:40:43 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// to deaclocate nodes (well, tokens)
void	deallocate(t_token **root)
{
	t_token	*curr;
	t_token	*token;

	if (!root || !*root)
		return ;
	curr = *root;
	while (curr != NULL)
	{
		token = curr;
		curr = curr->next;
		if (token->com)
            free(token->com);
		free(token);
	}
	*root = NULL;
}

void	close_free(t_token *tokens, t_shell *shell)
{
	deallocate(&tokens);
	free_array(shell->env_var);
}

bool	check_for_exit(char *command)
{
	if (ft_strcmp(command, "exit") == 0) //what if instead, we put exit in the exec fun. If not found, and is not "exit" or etc, then not found.?
	{
		free(command);
		return (true);
	}	
	return (false);
}
