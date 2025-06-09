/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 08:24:22 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	execute_single_cmd(char **cmd, t_shell *shell)
{
	char	*path;
	int		status;

	status = 0;
	if (!cmd[0] || !cmd)
		return ;
	path = get_cmd_path(cmd[0], shell);
	if (!path)
	{
		perror("Command not found");
		shell->exit_stat = 127;
		return ;
	}
	shell->pid1 = fork();
	if (shell->pid1 == -1)
		perror("fork");
	else if (shell->pid1 == 0)
	{
		if (execve(path, cmd, shell->env_var) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(shell->pid1, &status, 0);
		shell->exit_stat = WEXITSTATUS(status);
	}
	free(path);
}

bool	handle_builtin(char **cmd, t_shell *shell)
{
	if (!cmd || !cmd[0])
		return (false);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (print_env(*shell), true);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "$?") == 0)
		return (printf("%d\n", shell->exit_stat), true);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd, shell), true);
	return (false);
}

int	is_valid_directory(char *path)
{
	if (access(path, F_OK) == -1)
		return (perror("cd: No such file or directory"), 0);
	if (access(path, X_OK) == -1)
		return (perror("cd: Permission denied"), 0);
	return (1);
}
