/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:47:33 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/24 18:28:07 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_echo(char **cmd)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_option || cmd[i] == NULL)
		write(1, "\n", 1);
	return (i);
}

void	builtin_cd(char **cmd, t_shell *shell)
{
	char	*path;
	
	if (size_cmd_arg(cmd) > 2)
	{
		shell->exit_stat = 1;
		return ;
	}
	if (!cmd[1])
		path = get_cmd_path(cmd[0], shell);
	else
		path = cmd[1];
	if (!path || !is_valid_directory(path) || chdir(path) != 0)
	{
		shell->exit_stat = 1;
		return ;
	}
	else
		shell->pwd = set_pwd(shell);
	shell->exit_stat = 0;
}

void	builtin_pwd(t_shell *shell)
{
	if (!shell->pwd || !is_valid_directory(shell->pwd))
	{
		shell->exit_stat = 128;
		return ;
	}
	printf("%s\n", shell->pwd);
	shell->exit_stat = 0;
}

void	ft_export(char **cmd, t_shell *shell)
{
	char	*equal;
	int		i;

	i = 1;
	if (!cmd[i])
	{
		print_env(*shell);
		return ;
	}
	while (cmd[i])
	{
		equal = ft_strchr(cmd[i], '=');
		if (equal)
			set_var(cmd, shell, equal, i);
		i++;
	}
}

void	builtin_unset(char **cmd, t_shell *shell)
{
	int	pos;
	int	i;

	i = 1;
	while (cmd[i])
	{
		pos = search_env(shell, cmd[i]);
		if (pos >= 0)
		{
			free(shell->env_var[pos]);
			while (shell->env_var[pos])
			{
				shell->env_var[pos] = shell->env_var[pos + 1];
				pos++;
			}
		}
		i++;
	}
}
