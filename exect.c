/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/10 23:12:02 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static void	exec_fork_and_wait(char *path, char **cmd, t_shell *shell)
{
	int	status;

	shell->pid1 = fork();
	if (shell->pid1 == -1)
	{
		perror("fork");
		shell->exit_stat = 1;
		return ;
	}
	else if (shell->pid1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(path, cmd, shell->env_var) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	signal(SIGINT, SIG_IGN);
	waitpid(shell->pid1, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	shell->exit_stat = WEXITSTATUS(status);
	setup_shell_signals();
}

void	execute_single_cmd(char **cmd, t_shell *shell)
{
	char	*path;

	if (!cmd[0] || !cmd)
		return ;
	path = get_right_path(cmd[0], shell, 0);
	if (!path)
	{
		printf("%s: command not found\n", cmd[0]);
		shell->exit_stat = 127;
		return ;
	}
	exec_fork_and_wait(path, cmd, shell);
	if (path != cmd[0])
		free(path);
}

//printf("builtin used\n"); // for checking if builtin is used or not
bool	handle_builtin(char **cmd, t_shell *shell)
{
	if (!cmd || !cmd[0] || ft_strchr(*cmd, '/'))
		return (false);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (shell->exit_stat = 0, builtin_cd(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (shell->exit_stat = 0, builtin_pwd(shell), true);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (shell->exit_stat = 0, ft_export(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (shell->exit_stat = 0, print_env(*shell), true);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (shell->exit_stat = 0, builtin_unset(cmd, shell), true);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (shell->exit_stat = 0, ft_echo(cmd), true);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (shell->exit_stat = 0, ft_exit(cmd, shell), true);
	return (false);
}

int	is_valid_directory(char *path)
{
	struct stat	sb;

	if (access(path, F_OK) == -1)
		return (perror("cd: No such file or directory"), 0);
	else if (stat(path, &sb) == -1)
		return (perror("cd: stat error"), 0);
	else if (!S_ISDIR(sb.st_mode))
	{
		perror("cd: Not a directory");
		return (0);
	}
	else if (access(path, X_OK) == -1)
		return (perror("cd: Permission denied"), 0);
	return (1);
}
