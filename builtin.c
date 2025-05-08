/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:47:33 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/08 22:53:51 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_echo(char **cmd, t_shell *shell)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	shell->exit_stat = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
		{
			if (write(1, " ", 1) == -1)
				shell->exit_stat = 1;
		}
		i++;
	}
	if (n_option)
	{
		if (write(1, "\n", 1) == -1)
			shell->exit_stat = 1;
	}
	return (i);
}

void	builtin_cd(char **cmd, t_shell *shell)
{
	char	*path;
	char	**envp;
	int		i;

	i = 0;
	envp = shell->env_var;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		printf("invalid directory\n");
		return ;
	}
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
	if (!is_valid_directory(path))
	{
		shell->exit_stat = 1;
		return ;
	}
	if (is_valid_directory(path))
	{
		if (chdir(path) != 0)
		{
			perror("cd");
			shell->exit_stat = 1;
			return ;
		}
	}
	else
		shell->pwd = set_pwd(shell);
	shell->exit_stat = 0;
}

void	builtin_pwd(char **cmd, t_shell *shell)
{
	if (!shell->pwd)
	{
		shell->exit_stat = 128;
		return ;
	}
	if(!is_valid_directory(shell->pwd))
	{
		shell->exit_stat = 1;
		return ;
	}
	else 
		shell->exit_stat = 0;
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
