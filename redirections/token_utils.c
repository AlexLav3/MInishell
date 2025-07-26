/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:50:10 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/23 17:02:59 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
 * Utility to check if a given string is a redirection symbol
 * such as "<", ">", ">>", or "<<".
 */
int	is_redir(const char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0 || \
			ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
}

/*
 * Checks a token list to see if it includes any redirection operators.
 * Skips NULL `com` (empty) fields and returns 1 if any redirection is found.
 */
int	token_has_redir(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->com)
		{
			tokens = tokens->next;
			continue ;
		}
		if (ft_strcmp(tokens->com, "<") == 0 || \
			ft_strcmp(tokens->com, ">") == 0 || \
			ft_strcmp(tokens->com, ">>") == 0 || \
			ft_strcmp(tokens->com, "<<") == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	cleanup_child_and_exit(t_cmd *cmd, t_shell *shell, t_token **tokens,
		int status)
{
	if (tokens)
		deallocate(tokens);
	if (cmd)
		reset_redirection(cmd);
	if (shell)
	{
		if (shell->env_var)
			free_array(shell->env_var);
		if (shell->pwd)
			free(shell->pwd);
		if (shell->infile)
			free(shell->infile);
		if (shell->outfile)
			free(shell->outfile);
	}
	if (status != 100)
		exit(status);
}

t_grouped	build_group(t_shell *shell, t_cmd *cmds, int cmd_count,
					t_token **tokens)
{
	t_grouped	group;

	group = malloc(sizeof(struct s_grouped));
	if (!group)
		return (NULL);
	group->tokens = tokens;
	group->shell = shell;
	group->cmds = cmds;
	group->cmd_count = cmd_count;
	group->line = NULL;
	group->heredoc_pipe = false;
	return (group);
}

void	free_partial_args(char **args, int i)
{
	while (--i >= 0)
		free(args[i]);
	free(args);
}
