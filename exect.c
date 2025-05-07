/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/07 20:51:26 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//array creation
//cat test.txt | grep "42" | sort | wc -l
char	**make_args(t_token *tokens, t_shell *shell)
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
			if (!tokens->literal && ft_strchr(tokens->com, '$'))
			{
				cmd[i] = ft_strdup(tokens->com);
				cmd[i] = handle_dollar(cmd[i], shell);
			}
			else
			{
				cmd[i] = ft_strdup(tokens->com);
				if (!cmd[i])
				{
					while (i > 0)
						free(cmd[--i]);
					return (free(cmd), NULL);
				}
			}	
			i++;
		}
		tokens = tokens->next;
	}
	cmd[i++] = NULL;
	return (cmd);
}

bool	handle_builtin(char **cmd, t_shell *shell)
{
	int	status;

	status = 0;
	if (!cmd || !cmd[0])
		return (false);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (print_env(*shell), true);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd), true);
	// else if (ft_strcmp(cmd[0], "$?" ) == 0)
	return (false);
}

char 	*handle_dollar(char *cmd, t_shell *shell)
{
	int		idx;
	char	*env;
	char	*value;

	if (!cmd || cmd[0] != '$') // sanity check
		return (ft_strdup(cmd));

	idx = search_env(shell, cmd + 1); // shift to skip '$'
	if (idx >= 0)
	{
		env = shell->env_var[idx];	
		value = ft_strchr(env, '=');
		if (!value)
			return (ft_strdup(""));

		return (ft_strdup(value + 1)); 
	}
	else
		return (ft_strdup(""));
}
