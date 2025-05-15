/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/15 23:31:37 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//array creation
//cat test.txt | grep "42" | sort | wc -l
char	**make_args(t_token *tokens, t_shell *shell)
{
	char	**cmd;
	char	*pos;
	int		i;
	char	*expanded;

	i = 0;
	cmd = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmd || !tokens)
		return (NULL);
	while (tokens)
	{
		if (tokens->com && tokens->com[0] != '\0')
		{
			cmd[i] = toks_to_args(tokens, *cmd, shell);
			i++;
		}
		tokens = tokens->next;
	}
	cmd[i++] = NULL;
	return (cmd);
}

bool	handle_builtin(char **cmd, t_shell *shell)
{
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
		return (ft_echo(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "$?") == 0)
		return (printf("%d\n", shell->exit_stat), true);
	return (false);
}

char	*handle_dollar(char *cmd, t_shell *shell)
{
	int		idx;
	char	*env;
	char	*value;
	int		i;

	i = 0;
	if (!cmd || cmd[1] == '?')
		return (ft_strdup(cmd));
	while (cmd[i])
	{
		if (cmd[i] == '$')
			break ;
		i++;
	}
	idx = search_env(shell, cmd + (i + 1));
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

int	is_valid_directory(char *path)
{
	if (access(path, F_OK) == -1)
		return (perror("cd: No such file or directory"), 0);
	if (access(path, X_OK) == -1)
		return (perror("cd: Permission denied"), 0);
	return (1);
}

char	*toks_to_args(t_token *tokens, char *cmd, t_shell *shell)
{
	char 	*pos;
	char	*expanded;

	cmd = ft_strdup(tokens->com);
	if (!cmd)
		return (free(cmd), NULL);
	if (!tokens->literal && ft_strchr(tokens->com, '$') != NULL)
	{
		pos = ft_strchr(tokens->com, '$');
		expanded = handle_dollar(ft_strchr(tokens->com, '$'), shell);
		if (expanded)
		{
			printf("cmd here: %s\n", ft_strjoin(strndup(tokens->com, pos - tokens->com), expanded));
			return (ft_strjoin(strndup(tokens->com, pos - tokens->com), expanded));
		}
	}
	return cmd;
}
