#include "../Minishell.h"

// pipe_handle_001.c

/*
 * Simple error handler that prints a message using `perror`
 * and exits the program with failure.
 */
void	pipex_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
 * Counts how many commands are in a null-terminated string array.
 * Used to determine how many pipes/processes to set up.
 */
int	cmd_counter(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

/*
 * Manages closing pipe file descriptors after forking a child.
 * Closes read end from previous command and write end of current pipe.
 * Prepares `prev_fd` for the next command in the chain.
 */
void	fd_handle(int i, int cmd_count, t_shell *px)
{
	if (i > 0 && px->prev_fd[0] >= 0)
		close(px->prev_fd[0]);
	if (i < cmd_count - 1 && px->pipe_fd[1] >= 0)
		close(px->pipe_fd[1]);
	if (i < cmd_count - 1)
		px->prev_fd[0] = px->pipe_fd[0];
}

/*
 * Decides which child function to run based on position in pipeline:
 * first, middle, or last. Also closes unused FDs in each child.
 */
void	which_child(int i, int cmd_count, t_shell *px, char **cmds)
{
	if (i == 0)
		first_child_process(px, cmds[i]);
	else if (i == cmd_count - 1)
		last_child_process(px, cmds[i]);
	else
		middle_child_process(px, cmds[i]);
	if (i > 0)
		close(px->prev_fd[0]);
	if (i < cmd_count - 1)
		close(px->pipe_fd[1]);
}

/*
 * Main function to execute a sequence of piped commands.
 * Iterates through commands, sets up pipes and forks children.
 * Each child handles one command. Parent closes FDs and waits.
 */
void	create_pipes(char **cmds, t_shell *shell)
{
	int		i;
	int		cmd_count;
	t_shell	px;

	i = -1;
	init_pipex(&px, shell);
	cmd_count = cmd_counter(cmds);
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1)
			if (pipe(px.pipe_fd) == -1)
				pipex_error("Error creating pipe");
		px.pid = fork();
		if (px.pid == -1)
			pipex_error("Fork failed");
		if (px.pid == 0)
		{
			which_child(i, cmd_count, &px, cmds);
			exit(0);
		}
		fd_handle(i, cmd_count, &px);
	}
	close_pipes_and_wait(&px);
}
