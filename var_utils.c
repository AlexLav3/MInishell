/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:28:06 by fnagy             #+#    #+#             */
/*   Updated: 2025/07/31 10:27:54 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	set_var(char **cmd, t_shell *shell, char *equal, int i)
{
	char	*var;
	char	*name;

	var = ft_strdup(cmd[i]);
	if (!var)
		return ;
	*equal = '\0';
	name = cmd[i];
	if (!valid_name(name))
	{
		free(var);
		return ;
	}
	if (search_env(shell, name) < 0)
		add_env(shell, var);
	else
		update_env(shell, var, name);
	free(var);
	*equal = '=';
}

int	copy_env_vars(char **dest, char **src, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			while (i-- > 0)
				free(dest[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*expand_nested_dollar(char *suf, t_shell *shell)
{
	char	*tmp;

	tmp = handle_dollar(suf, shell);
	free(suf);
	return (tmp);
}

static char	*handle_var_exit_status(char *cmd, t_shell *shell,
				int i, char **suf)
{
	char	*value;

	value = ft_itoa(shell->exit_stat);
	*suf = ft_strdup(cmd + (i + 2));
	return (value);
}

static char	*handle_invalid_env(char c)
{
	if (c != ' ')
		return (ft_strdup(""));
	return (ft_strdup("$"));
}

static char	*handle_valid_env(t_shell *shell, char *prefix)
{
	char	*env;
	char	*value;

	env = shell->env_var[shell->env_idx];
	value = ft_strchr(env, '=');
	if (!value)
	{
		free(prefix);
		return (ft_strdup(""));
	}
	return (ft_strdup(value + 1));
}

char	*process_env_var(char *cmd, t_shell *shell, char *prefix, int i)
{
	char	*value;
	char	*suf;

	suf = NULL;
	if (cmd[i + 1] == '?')
		value = handle_var_exit_status(cmd, shell, i, &suf);
	else if (shell->env_idx < 0)
		value = handle_invalid_env(cmd[i + 1]);
	else
		value = handle_valid_env(shell, prefix);
	if (cmd[i + 1] != '?')
		suf = ft_strdup(cmd + (i + 1) + shell->var_len);
	if (ft_strchr(suf, '$'))
		suf = expand_nested_dollar(suf, shell);
	return (join_and_free(prefix, join_and_free(value, suf)));
}

// char	*process_env_var(char *cmd, t_shell *shell, char *prefix, int i)
// {
// 	char	*env;
// 	char	*value;
// 	char	*suf = NULL;

// 	value = NULL;
// 	if (cmd[i + 1] == '?')
// 	{
// 		value = ft_itoa(shell->exit_stat);
// 		suf = ft_strdup(cmd + (i + 2));
// 	}
// 	else if (shell->env_idx < 0)
// 	{
// 		if(cmd[i + 1] != ' ')
// 			value = ft_strdup("");
// 		else 
// 			value = ft_strdup("$");
// 	}
// 	else if (shell->env_idx >= 0)
// 	{
// 		env = shell->env_var[shell->env_idx];
// 		value = ft_strchr(env, '=');
// 		if (!value)
// 			return (free(prefix), ft_strdup(""));
// 		value = ft_strdup(value + 1);
// 	}
// 	if (cmd[i + 1] != '?')
// 		suf = ft_strdup(cmd + (i + 1) + shell->var_len);
// 	if (ft_strchr(suf, '$') != NULL)
// 		suf = expand_nested_dollar(suf, shell);
// 	return (join_and_free(prefix, join_and_free(value, suf)));
// }

int	valid_name(char *name)
{
	if (name[0] >= '0' && name[0] <= '9')
		return (printf("invalid!\n"), 0);
	while (*name)
	{
		if (*name == ' ' || *name == '-' || *name == '+' || *name == '!'
			|| *name == '@' || *name == '%' || *name == '=')
			return (printf("invalid\n"), 0);
		name++;
	}
	return (1);
}
