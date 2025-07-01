#include <../Minishell.h>

//heredoc.c

/*
 * Child process responsible for reading heredoc input line-by-line
 * until the specified delimiter is encountered. Each line is written
 * to the write-end of the heredoc pipe.
 */
static void	heredoc_child_process(int write_fd, char *delimiter)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(write_fd);
	exit(0);
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
static pid_t	create_heredoc_child(int pipe_fd[2], char *delimiter)
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
		heredoc_child_process(pipe_fd[1], delimiter);
	}
	return (pid);
}

/*
 * Parent process after forking heredoc child.
 * - Waits for child to finish
 * - If interrupted by SIGINT, sets error and closes pipe
 * - Otherwise, stores read-end of pipe for command input
 */
static void	handle_heredoc_parent(t_cmd *cmd, t_shell *shell,
									int pipe_fd[2], pid_t pid)
{
	int	status;
	

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exit_stat = 130;
		close(pipe_fd[0]);
		cmd->redir_in = -1;
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
void	heredoc_do(t_cmd *cmd, t_shell *shell, char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (init_heredoc_pipe(pipe_fd) == -1)
		return ;
	pid = create_heredoc_child(pipe_fd, delimiter);
	if (pid == -1)
	{
		cmd->redir_error = 1;
		return ;
	}
	if (pid > 0)
		handle_heredoc_parent(cmd, shell, pipe_fd, pid);
}
