/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:38:04 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/21 19:40:31 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

t_grouped	g_global = NULL;

/*
 * Child process responsible for reading heredoc input line-by-line
 * until the specified delimiter is encountered. Each line is written
 * to the write-end of the heredoc pipe.
 */
static void	heredoc_child_process(int write_fd, char *delimiter,
		t_grouped group)
{
	char	*line;

	g_global = group;
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("heredoc> ");
		group->line = line;
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
		group->line = NULL;
	}
	if (line)
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
		perror("waitpid");
		group->shell->exit_stat = 130;
		close(pipe_fd[0]);
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
void	heredoc_do(t_cmd *cmd, t_shell *shell, char *delimiter,
		t_token **tokens)
{
	int			pipe_fd[2];
	pid_t		pid;
	t_grouped	group;

	group = build_group(shell, cmd, 1, tokens);
	if (!group)
	{
		close_free(tokens, shell);
		return ;
	}
	if (init_heredoc_pipe(pipe_fd) == -1)
	{
		close_free(tokens, shell);
		return ;
	}
	pid = create_heredoc_child(pipe_fd, delimiter, group);
	if (pid == -1)
	{
		cmd->redir_error = 1;
		close_free(tokens, shell);
		return ;
	}
	if (pid > 0)
		handle_heredoc_parent(cmd, group, pipe_fd, pid);
	free(group);
}
