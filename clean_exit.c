/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:07:17 by ferenc            #+#    #+#             */
/*   Updated: 2025/07/19 02:18:25 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// void	free_cmd(t_cmd *cmd)
// {
// 	if (!cmd)
// 		return ;

// 	if (cmd->args)
// 		free_array(cmd->args);
// 	if (cmd->infile)
// 		free(cmd->infile);
// 	if (cmd->outfile)
// 		free(cmd->outfile);

// 	free(cmd);
// }

// void	free_cmd_array(t_cmd *cmds, int count)
// {
// 	int	i;

// 	if (!cmds)
// 		return ;

// 	i = 0;
// 	while (i < count)
// 	{
// 		if (cmds[i].args)
// 			free_array(cmds[i].args);
// 		free(cmds[i].infile);
// 		free(cmds[i].outfile);
// 		i++;
// 	}
// 	free(cmds);
// }

void	deallocate(t_token **root)
{
	t_token	*curr;
	t_token	*token;
	int		count = 0;

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
		// arr[i] = NULL; // update
		i++;
	}
	free(arr);
	// arr = NULL; // update - HUH?
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
