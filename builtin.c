/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:47:33 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/16 03:24:25 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_echo(char **cmd, t_shell *shell)
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
		if(cmd[i + 1])
		{
			if (cmd[i + 1][0] != '\'' && cmd[i + 1][0] != '\"' && cmd[i][0] != '\"')
				write(1, " ", 1);
		}
		i++;
	}
	if (n_option || cmd[i] == NULL)
		write(1, "\n", 1);
	return (i);
}

void	builtin_cd(char **cmd, t_shell *shell)
{
	char	*path;
	char	**envp;
	
	envp = shell->env_var;
	if(size_cmd_arg(cmd) > 2)
		return ;
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

void	builtin_pwd(char **cmd, t_shell *shell)
{
	if (!shell->pwd || !is_valid_directory(shell->pwd))
	{
		shell->exit_stat = 128;
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
			if (search_env(shell, name) < 0)
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
		if (pos >= 0)
		{
			shell->env_var[pos] = NULL;
			break ;
		}
		i++;
	}
}

void ft_exit(char **cmd, t_shell *shell)
{
	if(size_cmd_arg(cmd) > 1)
	{
		printf("too many args\n");
		return;
	}
	else 
		shell->exit = 1;
}