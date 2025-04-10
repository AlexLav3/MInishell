/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:17 by ferenc            #+#    #+#             */
/*   Updated: 2025/04/10 03:12:23 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	split_by_pipe(t_shell *shell, char **cmd)
{
	int	i;
	int	j;
	int	k;
	int	count;
	int	seg_len;

	i = 0;
	j = 0;
	count = count_seps(cmd, '|');
	shell->av = malloc(sizeof(char **) * (count + 1));
	if (!shell->av)
		return ;
	while (cmd[i])
	{
		seg_len = count_segment_tokens(cmd, i, '|');
		shell->av[j] = malloc(sizeof(char *) * (seg_len + 1));
		if (!shell->av[j])
		{
			while (j > 0)
			{
				free(shell->av[j - 1]);
				j--;
			}
			free(shell->av);
			return ;
		}
		k = 0;
		while ((cmd[i] && !(cmd[i][0] == '|' && cmd[i][1] == '\0')))
			shell->av[j][k++] = cmd[i++];
		shell->av[j][k] = NULL;
		if (cmd[i]) // why not if( == '|')
			i++; // skip the '|'
		j++;
	}
	shell->av[j] = NULL;
}

void	execute_pipeline(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->av[i])
		i++;
	handle_pipeline(shell, 0, -1);
	// Just wait for all child processes
	while (wait(NULL) > 0)
		; //empty while? wait is supposed to already wait by itself, doesnt'it? 
	free_av(shell->av);
}

void	handle_pipeline(t_shell *shell, int index, int input_fd)
{
	int		pipe_fd[2];
	int		is_last;
	int		output_fd;
	pid_t	pid;
		char *path;

	if (shell->av[index] == NULL)
		return ;
	is_last = shell->av[index + 1] == NULL;
	if (!is_last && pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return ;
	}
	if (is_last)
		output_fd = -1;
	else
		output_fd = pipe_fd[1];
	pid = fork();
	if (pid == 0)
	{
		if (input_fd != -1)
			dup2(input_fd, STDIN_FILENO);
		if (output_fd != -1)
			dup2(output_fd, STDOUT_FILENO);
		if (input_fd != -1)
			close(input_fd);
		if (!is_last)
			close(pipe_fd[0]);
		path = get_cmd_path(shell->av[index][0], shell);
		if (!path)
		{
			perror("Command not found");
			exit(127);
		}
		execve(path, shell->av[index], shell->env_var);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else if (!is_last)
	{
		close(pipe_fd[1]);
		handle_pipeline(shell, index + 1, pipe_fd[0]);
		close(pipe_fd[0]);
	}
}

// void execute_command(char **cmd, int input_fd, int output_fd, t_shell *shell)
// {
// 	char *path;
// 	pid_t pid = fork();

// 	if (pid == 0)
// 	{
// 		if (input_fd != -1)
// 		{
// 			dup2(input_fd, STDIN_FILENO);
// 			close(input_fd);
// 		}
// 		if (output_fd != -1)
// 		{
// 			dup2(output_fd, STDOUT_FILENO);
// 			close(output_fd);
// 		}
// 		path = get_cmd_path(cmd[0], shell);
// 		if (!path)
// 		{
// 			perror("Command not found");
// 			exit(127);
// 		}
// 		execve(path, cmd, shell->env_var);
// 		perror("execve failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid > 0)
// 		shell->pipe_pid = pid;
// }