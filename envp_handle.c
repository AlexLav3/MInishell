/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:53:36 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/15 14:30:56 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// printing envp
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
	int		len;

	i = 0;
	count = 0;
	while (shell->env_var[count])
		count++;
	len = ft_strlen(var) + count;
	new_envp = malloc(sizeof(char *) * (len) + 1);
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
	new_envp[i] = ft_strdup(var);
	shell->env_var = copy_envp(new_envp);
}

int	search_env(t_shell *shell, char *var)
{
	int		i;
	size_t	len;
	char	*equal;
	char	*dup;
	char	*name;

	dup = ft_strdup(var);
	i = 0;
	while (dup[i])
	{
		equal = ft_strchr(&dup[i], '=');
		if (equal)
		{
			*equal = '\0';
			name = &dup[i];
			len = ft_strlen(name);
			break ;
		}
		i++;
	}
	while (shell->env_var[i])
	{
		if (ft_strncmp(shell->env_var[i], name, len) == 0
			&& shell->env_var[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	update_env(t_shell *shell, char *var)
{
	
	
}
