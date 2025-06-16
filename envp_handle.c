/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:53:36 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/30 13:51:28 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	print_env(t_shell shell)
{
	int	i;

	if (!shell.env_var)
	{
		printf("No environment variables.\n");
		return ;
	}
	i = 0;
	while (shell.env_var[i] != NULL)
		printf("%s\n", shell.env_var[i++]);
}

char	**copy_envp(char **envp, char *new_var)
{
	int		count;
	char	**copy;

	count = 0;
	while (envp[count])
		count++;								//pls tell me what you're trying to do with this check (below this line)
	copy = malloc(sizeof(char *) * (count + 1 + (new_var != NULL)));
	if (!copy)
		return (NULL);
	if (!copy_env_vars(copy, envp, count))
		return (free(copy), NULL);
	if (new_var)
	{
		copy[count] = ft_strdup(new_var);
		if (!copy[count])
		{
			while (count-- > 0)
				free(copy[count]);
			return (free(copy), NULL);
		}
	}			//here too
	copy[count + (new_var != NULL)] = NULL;
	return (copy);
}

void	add_env(t_shell *shell, char *var)
{
	char	**new_envp;
	int		i;

	new_envp = copy_envp(shell->env_var, var);
	if (!new_envp)
		return ;
	i = 0;
	while (shell->env_var[i])
		free(shell->env_var[i++]);
	free(shell->env_var);
	shell->env_var = new_envp;
}

int	search_env(t_shell *shell, char *var)
{
	int		i;
	size_t	len;

	len = 0;
	i = 0;
	if (!var)
		return (0);
	while (var[len])
	{							//as not caps are allowed, I'll change this condition.
		if (var[len] == '\'' || (var[len] < 65 || var[len] > 90))
			break ;
		len++;
	}
	shell->var_len = len;
	while (shell->env_var[i])
	{
		if (ft_strncmp(shell->env_var[i], var, len) == 0
			&& shell->env_var[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env(t_shell *shell, char *var, char *name)
{
	int	pos;

	pos = search_env(shell, name);
	if (pos >= 0)
	{
		free(shell->env_var[pos]);
		shell->env_var[pos] = ft_strdup(var);
	}
}
