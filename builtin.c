/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:47:33 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/17 11:21:11 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

bool	handle_builtin(char **cmd, t_shell *shell)
{
	if (!cmd || !cmd[0])
		return (0);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd, shell), 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd, shell), 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, shell), 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (print_env(*shell), 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(cmd, shell), 1);
	return (0);
}
/*
NOTE: Using the cd command without any arguments or
with more than one argument doesn't affect the current directory path.
Make sure this edge case is handled in a way that prevents crashes.

simple cd is okay, but cd .. /music will lead to home directory
*/
void	builtin_cd(char **cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	envp = shell->env_var;
	if (!cmd[1])
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, "HOME=", 5) == 0)
			{
				path = *envp + 5;
				break ;
			}
			envp++;
		}
	}
	else
		path = cmd[1];
	if (!path)
		return ;
	if (chdir(path) != 0)
		perror("cd");
	else
		shell->pwd = set_pwd(shell);
}

void	builtin_pwd(char **cmd, t_shell *shell)
{
	if (!shell->pwd)
		return ;
	//printf("custom function; %s\n", shell->pwd);
	//used to check if it was using the custom function or not.
	printf("%s\n", shell->pwd);
}

void	ft_export(char **cmd, t_shell *shell)
{
	char	*var;
	char	*name;
	char	*equal;
	char	*value;
	int		i;

	i = 0;
	while (cmd[i])
	{
		equal = ft_strchr(cmd[i], '=');
		if (equal)
		{
			var = ft_strdup(cmd[i]);
			*equal = '\0';
			name = cmd[i];
			if (!search_env(shell, name))
				add_env(shell, var);
			else
				update_env(shell, var, name);
			break ;
		}
		i++;
	}
	if (!equal)
		print_env(*shell);
}

void	builtin_unset(char **cmd, t_shell *shell)
{
	char	*var;
	int		pos;
	int		i;

	pos = 0;
	i = 0;
	while (cmd[i])
	{
		var = cmd[i];
		pos = search_env(shell, var);
		if (pos)
		{
			shell->env_var[pos] = NULL;
			break ;
		}
		i++;
	}
}
