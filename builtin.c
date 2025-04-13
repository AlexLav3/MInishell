/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:47:33 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/13 03:00:44 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

bool	handle_builtin(char **cmd, t_shell *shell)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		builtin_cd(cmd, shell);
		return (1);
	}
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
}
