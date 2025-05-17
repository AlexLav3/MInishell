/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:57 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 07:47:33 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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
	free(shell->pwd);
}

void	ft_exit(char **cmd, t_shell *shell)
{
	if (size_cmd_arg(cmd) > 1)
	{
		printf("too many args\n");
		return ;
	}
	else
		shell->exit = 1;
}
