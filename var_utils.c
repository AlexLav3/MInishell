/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:28:06 by fnagy             #+#    #+#             */
/*   Updated: 2025/06/16 16:27:43 by elavrich         ###   ########.fr       */
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
	if (search_env(shell, name) < 0)
		add_env(shell, var);
	else
		update_env(shell, var, name);
	free(var);
	*equal = '=';
}

int	copy_env_vars(char **dest, char **src, int count)
{
	int	i;

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

char	*process_env_var(char *cmd, t_shell *shell, char *prefix, int i)
{
	char	*env;
	char	*value;
	char	*suf;

	env = shell->env_var[shell->env_idx];
	value = ft_strchr(env, '=');
	if (!value)
		return (free(prefix), ft_strdup(""));
	value = value + 1;
	suf = ft_strdup(cmd + (i + 1) + shell->var_len);
	if (ft_strchr(suf, '$') != NULL)
		suf = expand_nested_dollar(suf, shell);
	return (join_and_free(prefix, join_and_free(ft_strdup(value), suf)));
}
