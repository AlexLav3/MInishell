/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:47:33 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/13 06:51:39 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

bool	handle_builtin(char **cmd, t_shell *shell)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd, shell), 1);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd, shell), 1);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, shell), 1);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (print_env(*shell), 1);
	return (0);
}

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
	char	*equal;
	int		i;

	i = 0;
	while (cmd[i])
	{
		//if find equal sign
		equal = ft_strchr(cmd[i], '=');
		if (equal)
			var = ft_strdup(cmd[i]);
		//add to shell for now, but will need to implement if exists, replace.
		add_env(shell, var);
		i++;
	}
}

void	add_env(t_shell *shell, char *var)
{
	int		count;
	char	**new_envp;
	int		i;

	i = 0;
	count = 0;
	new_envp = copy_envp(shell->env_var); //I think there is not enough space in malloc for the new var
	while (shell->env_var[count])
		count++;
	// new_envp[count] = var;
	// new_envp[count + 1] = NULL;
	// shell->env_var = new_envp; 
}
