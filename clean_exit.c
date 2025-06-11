/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:57 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/11 14:30:12 by ferenc           ###   ########.fr       */
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

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	// arr = NULL;
}

void	close_free(t_token *tokens, t_shell *shell)
{
	//do you think we can make a checker for if any child process hasn't been closed?
	//fine if not, I just think it would be good practice and a nice thing to have, thoughts?
	/*
		what type of checker do you mean?
		we have: while (wait(NULL) > 0)
		which means to wait for all the child processes to finish before carry on.
		it is in the close_pipes_and_wait() funciton
	*/
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
