/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:34:41 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/16 22:38:01 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
 * Checks if the token list contains any pipe (`|`) symbols.
 * Used to decide whether to enter pipe execution logic.
 */
int	token_has_pipe(t_token **tokens)
{
	t_token	*curr;

	if (!tokens || !*tokens)
		return (0);
	curr = *tokens;
	while (curr)
	{
		if (curr->com && is_pipe(curr->com[0]))
			return (1);
		curr = curr->next;
	}
	return (0);
}

/*
 * Builds command strings from tokens.
 * On pipe token, finalizes current command and moves to next.
 * Otherwise, adds token to current command string.
 */
char	*process_token(t_token *token, char *cmd_str, char **cmds, int *i)
{
	char	*tmp;

	if (is_pipe(token->com[0]))
	{
		cmds[(*i)++] = cmd_str;
		cmd_str = NULL;
	}
	else
	{
		if (cmd_str)
		{
			tmp = ft_strjoin(" ", token->com);
			cmd_str = join_and_free(cmd_str, tmp);
		}
		else
			cmd_str = ft_strdup(token->com);
	}
	return (cmd_str);
}

/*
 * Converts a token list into an array of command strings split by pipes.
 * Each element in the array is a command (with args) to be executed.
 */
char	**make_args_pipes(t_token **tokens)
{
	char	**cmds;
	char	*cmd_str;
	t_token	*curr;
	int		i;

	if (!tokens || !*tokens)
		return (NULL);
	curr = *tokens;
	cmds = malloc(sizeof(char *) * (size_args(curr) + 1));
	if (!cmds)
		return (NULL);
	cmd_str = NULL;
	i = 0;
	while (curr)
	{
		if (curr->com && curr->com[0] != '\0')
			cmd_str = process_token(curr, cmd_str, cmds, &i);
		curr = curr->next;
	}
	if (cmd_str)
		cmds[i++] = cmd_str;
	cmds[i] = NULL;
	return (cmds);
}

/*
 * Searches `$PATH` for the full path to a given command.
 * Returns the first matching executable path, or NULL if not found.
 */
char	*get_path_in(char *cmd, t_shell *px)
{
	int		i;
	char	*full_path;
	char	**paths;

	i = 0;
	full_path = NULL;
	while (px->env_var[i] && strncmp(px->env_var[i], "PATH=", 5))
		i++;
	if (!px->env_var[i])
		return (NULL);
	paths = ft_split(px->env_var[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}
