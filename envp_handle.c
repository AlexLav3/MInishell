/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:53:36 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/15 12:04:47 by ferenc           ###   ########.fr       */
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
	while (shell.env_var[i])
	{
		write(STDOUT_FILENO, shell.env_var[i], ft_strlen(shell.env_var[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

char	**copy_envp(char **envp, char *new_var)
{
	size_t	count;
	char	**copy;
	int		extra;

	extra = (new_var != NULL);
	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1 + extra));
	if (!copy)
		return (NULL);
	ft_memset(copy, 0, sizeof(char *) * (count + 1 + extra));
	if (!copy_env_vars(copy, envp, count))
		return (free(copy), NULL);
	if (new_var)
	{
		copy[count] = ft_strdup(new_var);
		if (!copy[count])
		{
			free_array(copy);
			return (NULL);
		}
	}
	copy[count + extra] = NULL;
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

	if (!var || !shell || !shell->env_var)
		return (-1);
	len = 0;
	i = 0;
	if (!var)
		return (0);
	if (var[0] == '?')
		return (i);
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	if (len <= 0)
		return (-1); 
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
	int		pos;
	char	*new_val;

	if (!shell || !shell->env_var || !var || !name)
		return ;
	pos = search_env(shell, name);
	if (pos >= 0)
	{
		new_val = ft_strdup(var);
		if (!new_val)
			return ;
		free(shell->env_var[pos]);
		shell->env_var[pos] = new_val;
	}
}
