/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:07:17 by ferenc            #+#    #+#             */
/*   Updated: 2025/07/20 18:41:10 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	deallocate(t_token **root)
{
	t_token	*curr;
	t_token	*token;
	int		count;

	count = 0;
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
		count++;
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
}

void	close_free(t_token **tokens, t_shell *shell)
{
	if (tokens)
		deallocate(tokens);
	if (shell)
	{
		if (shell->env_var)
		{
			free_array(shell->env_var);
			shell->env_var = NULL;
		}
		if (shell->pwd)
			free(shell->pwd);
		if (shell->infile)
			free(shell->infile);
		if (shell->outfile)
			free(shell->outfile);
	}
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

void	cleanup(char **args, t_shell *px, t_token **tokens, char **cmds)
{
	free_array(args);
	free_array(px->env_var);
	free(px->pwd);
	deallocate(tokens);
	free_array(cmds);
}
