/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:49:05 by ferenc            #+#    #+#             */
/*   Updated: 2025/03/04 14:29:26 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**arguments;
	char	*path;

	arguments = ft_split(cmd, ' ');
	if (!arguments)
		pipex_error("Failed to split commands");
	path = get_cmd_path(arguments[0], envp);
	if (!path)
	{
		free_array(arguments);
		pipex_error("Command not found");
	}
	if (execve(path, arguments, envp) == -1)
	{
		perror("Command not found");
		free_array(arguments);
		free(path);
		exit(127);
	}
}

int	create_pipex(char **av, char **envp)
{
	t_pipex	px;

	px.av = av;
	px.envp = envp;
	if (open_files(&px) == -1)
		return (-1);
	if (pipe(px.pipe_fd) == -1)
		pipex_error("Error creating pipe");
	px.pid1 = fork();
	if (px.pid1 == -1)
		pipex_error("Fork failed for cmd1");
	if (px.pid1 == 0)
		first_child_process(&px);
	px.pid2 = fork();
	if (px.pid2 == -1)
		pipex_error("Fork failed for cmd2");
	if (px.pid2 == 0)
		second_child_process(&px);
	close_pipes_and_wait(&px);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit(1);
	}
	create_pipex(av, envp);
	return (0);
}
