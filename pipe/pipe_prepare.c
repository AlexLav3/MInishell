/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:48:38 by ferenc            #+#    #+#             */
/*   Updated: 2025/04/17 09:55:18 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	token_has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->com && ft_strcmp(tokens->com, "|") == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

char	*str_join_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

void	process_token(t_token *token, char **cmd_str, char **cmds, int *i)
{
	char	*tmp;

	if (ft_strncmp(token->com, "|", 2) == 0)
	{
		cmds[(*i)++] = *cmd_str;
		*cmd_str = NULL;
	}
	else
	{
		if (*cmd_str)
		{
			tmp = ft_strjoin(" ", token->com);
			*cmd_str = str_join_free(*cmd_str, tmp);
		}
		else
			*cmd_str = ft_strdup(token->com);
	}
}

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

char	*get_path_in(char *cmd, t_shell *px)
{
	int		i;
	char	*full_path;
	char	**paths;

	i = 0;
	full_path = NULL;
	while (px->envp[i] && strncmp(px->envp[i], "PATH=", 5))
		i++;
	if (!px->envp[i])
		return (NULL);
	paths = ft_split(px->envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
