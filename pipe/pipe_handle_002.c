#include "../Minishell.h"

// pipe_handle_002.c

/*
 * Handles the first command in a pipeline.
 * Redirects STDOUT to pipe write end and executes the command.
 */
void	first_child_process(t_shell *px, char *cmd)
{
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 failed for first child");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
}

/*
 * Handles the last command in a pipeline.
 * Redirects STDIN from pipe read end and executes the command.
 */
void	last_child_process(t_shell *px, char *cmd)
{
	if (dup2(px->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 failed for last child");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
}

/*
 * Handles intermediate commands in a pipeline.
 * Redirects STDIN from previous pipe read end,
 * and STDOUT to current pipe write end, then executes.
 */
void	middle_child_process(t_shell *px, char *cmd)
{
	if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 failed for intermediate child (stdin)");
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 failed for intermediate child (stdout)");
	close(px->prev_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
	exit(0);
}

/*
 * Closes all remaining pipe FDs in the parent process.
 * Waits for all child processes to finish using `wait`.
 */
void	close_pipes_and_wait(t_shell *px)
{
	if (px->pipe_fd[0] != -1) // >= 0 change back all
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] != -1)
		close(px->pipe_fd[1]);
	if (px->prev_fd[0] != -1)
		close(px->prev_fd[0]);
	if (px->prev_fd[1] != -1)
		close(px->prev_fd[1]);
	while (wait(NULL) > 0)
		;
}
/*
 * Parses a command string into args and searches for the binary path.
 * If found, executes the command with `execve`, else prints an error.
 */
void	execute_cmd(char *cmd, t_shell *px)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		pipex_error("split");
	path = get_right_path(args[0], px, 1);
	if (!path)
		pipex_error("command not found");
	if (execve(path, args, px->envp) == -1)
		pipex_error("execve");
}
