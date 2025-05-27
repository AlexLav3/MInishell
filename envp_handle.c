/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:53:36 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/27 12:11:01 by fnagy            ###   ########.fr       */
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

char	**copy_envp(char **envp)
{
	int		count;
	int		i;
	char	**copy;

	count = 0;
	i = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

void	add_env(t_shell *shell, char *var)
{
	int		count;
	char	**new_envp;
	int		i;

	i = 0;
	count = 0;
	while (shell->env_var[count])
		count++;
	// allocate space for count + 2 pointers
	// (old env + new var + NULL terminator),
	// not sum of string lengths.
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return ;
	while (i < count)
	{
		new_envp[i] = ft_strdup(shell->env_var[i]);
		if (!new_envp[i])
		{
			while (i-- > 0)
				free(new_envp[i]);
			free(new_envp);
			return ;
		}
		i++;
	}
	new_envp[i++] = ft_strdup(var);
	new_envp[i] = NULL;
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
	{
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
