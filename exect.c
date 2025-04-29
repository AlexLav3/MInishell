/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/29 19:22:33 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//array creation
//cat test.txt | grep "42" | sort | wc -l
char	**make_args(t_token *tokens)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmd || !tokens)
		return (NULL);
	while (tokens)
	{
		if (tokens->com && tokens->com[0] != '\0')
		{
			cmd[i] = ft_strdup(tokens->com);
			if (!cmd[i])
			{
				while (i > 0)
					free(cmd[--i]);
				return (free(cmd), NULL);
			}
			i++;
		}
		tokens = tokens->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

bool	handle_builtin(char **cmd, t_shell *shell)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd, shell), 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd, shell), 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, shell), 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (print_env(*shell), 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(cmd, shell), 1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd, shell), 1);
	return (0);
}

int	handle_dollar(char *cmd, t_shell *shell)
{
	char	*var;
	int		idx;
	char	*env;
	char 	*value;

	idx = search_env(shell, cmd);
	if (idx)
	{
		env = shell->env_var[idx];
		value = ft_strchr(env, '=') + 1; // skip to after '='
		ft_putstr_fd(value, 1);
	}
	return (1);
}
