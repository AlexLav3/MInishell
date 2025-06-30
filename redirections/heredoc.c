#include <../Minishell.h>

//heredoc.c
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

static int	init_heredoc_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		pipex_error("Error creating pipe");
		return (-1);
	}
	return (0);
}

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
