/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:34:41 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/15 12:02:45 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
 * Checks if the token list contains any pipe (`|`) symbols.
 * Used to decide whether to enter pipe execution logic.
 */
int	token_has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->com && is_pipe(tokens->com[0]))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

/*
 * Builds command strings from tokens.
 * On pipe token, finalizes current command and moves to next.
 * Otherwise, adds token to current command string.
 */
void	process_token(t_token *token, char **cmd_str, char **cmds, int *i)
{
	char	*tmp;

	if (is_pipe(token->com[0]))
	{
		cmds[(*i)++] = *cmd_str;
		*cmd_str = NULL;
	}
	else
	{
		if (*cmd_str)
		{
			tmp = ft_strjoin(" ", token->com);
			*cmd_str = join_and_free(*cmd_str, tmp);
		}
		else
			*cmd_str = ft_strdup(token->com);
	}
}

/*
 * Converts a token list into an array of command strings split by pipes.
 * Each element in the array is a command (with args) to be executed.
 */
char	**make_args_pipes(t_token *tokens)
{
	char	**cmds;
	char	*cmd_str;
	int		i;

	cmds = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmds)
		return (NULL);
	cmd_str = NULL;
	i = 0;
	while (tokens)
	{
		if (tokens->com && tokens->com[0] != '\0')
			process_token(tokens, &cmd_str, cmds, &i);
		tokens = tokens->next;
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
