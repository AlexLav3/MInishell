/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:38:04 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/27 14:47:04 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

/*
 * Child process responsible for reading heredoc input line-by-line
 * until the specified delimiter is encountered. Each line is written
 * to the write-end of the heredoc pipe.
 */
static void	heredoc_child_process(int write_fd, char *delimiter,
		t_grouped group)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			close(write_fd);
			cleanup_heredoc_and_exit(NULL, group, 1);
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(write_fd);
	cleanup_heredoc_and_exit(NULL, group, 0);
}

/*
 * Creates a pipe to hold heredoc input. Returns -1 on failure.
 */
static int	init_heredoc_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		pipex_error("Error creating pipe");
		return (-1);
	}
	return (0);
}

/*
 * Forks a child process that writes heredoc input into the pipe.
 * In the child, closes read end and calls `heredoc_child_process`.
 */
static pid_t	create_heredoc_child(int pipe_fd[2], char *delimiter,
		t_grouped group)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		pipex_error("fork failed");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		heredoc_child_process(pipe_fd[1], delimiter, group);
	}
	return (pid);
}

/*
 * Parent process after forking heredoc child.
 * - Waits for child to finish
 * - If interrupted by SIGINT, sets error and closes pipe
	- this is not happening
 * - Otherwise, stores read-end of pipe for command input
 */
static void	handle_heredoc_parent(t_cmd *cmd, t_grouped group, int pipe_fd[2],
		pid_t pid)
{
	int	status;

	status = 0;
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		group->shell->exit_stat = 128 + WTERMSIG(status);
		cmd->redir_error = 1;
		close(pipe_fd[0]);
		cmd->redir_in = -1;
		reset_redirection(cmd);
	}
	else
		cmd->redir_in = pipe_fd[0];
}

/*
 * Orchestrates the heredoc creation process.
 * - Initializes the pipe
 * - Forks child to read heredoc input
 * - Handles parent logic and stores input fd
 * Marks the command as errored on any failure.
 */
void	heredoc_do(t_cmd *cmd, t_grouped group, char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (token_has_pipe(group->tokens))
		group->heredoc_pipe = true;
	if (init_heredoc_pipe(pipe_fd) == -1)
		return (cleanup_heredoc_and_exit(cmd, group, 100));
	pid = create_heredoc_child(pipe_fd, delimiter, group);
	if (pid == -1)
	{
		cmd->redir_error = 1;
		cleanup_heredoc_and_exit(cmd, group, 100);
		return ;
	}
	if (pid > 0)
		handle_heredoc_parent(cmd, group, pipe_fd, pid);
}
