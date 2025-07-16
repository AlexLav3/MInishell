

#include "../Minishell.h"

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
	cmd_count = size_cmd_arg(cmds);
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


#include "../Minishell.h"

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
}

/*
 * Closes all remaining pipe FDs in the parent process.
 * Waits for all child processes to finish using `wait`.
 */
void	close_pipes_and_wait(t_shell *px)
{
	// int		status;
	// pid_t	pid;

	if (px->pipe_fd[0] != -1)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] != -1)
		close(px->pipe_fd[1]);
	if (px->prev_fd[0] != -1)
		close(px->prev_fd[0]);
	if (px->prev_fd[1] != -1)
		close(px->prev_fd[1]);
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
	if (handle_builtin(args, px))
		exit(0);
	else
	{
		path = get_right_path(args[0], px, 1);
		if (!path)
		{
			write(STDERR_FILENO, args[0], ft_strlen(args[0]));
			write(STDERR_FILENO, ": command not found\n", 21);
			free_array(args);
			exit(127);
		}
	}
	if (execve(path, args, px->env_var) == -1)
	{
		pipex_error("execve");
		exit(127);
	}
}


#include "../Minishell.h"

/*
 * Checks if the token list contains any pipe (`|`) symbols.
 * Used to decide whether to enter pipe execution logic.
 */
int	token_has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->com && is_pipe(tokens->com[0]))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

/*
 * Builds command strings from tokens.
 * On pipe token, finalizes current command and moves to next.
 * Otherwise, adds token to current command string.
 */
void	process_token(t_token *token, char **cmd_str, char **cmds, int *i)
{
	char	*tmp;

	if (is_pipe(token->com[0]))
	{
		cmds[(*i)++] = *cmd_str;
		*cmd_str = NULL;
	}
	else
	{
		if (*cmd_str)
		{
			tmp = ft_strjoin(" ", token->com);
			*cmd_str = join_and_free(*cmd_str, tmp);
		}
		else
			*cmd_str = ft_strdup(token->com);
	}
}

/*
 * Converts a token list into an array of command strings split by pipes.
 * Each element in the array is a command (with args) to be executed.
 */
char	**make_args_pipes(t_token *tokens)
{
	char	**cmds;
	char	*cmd_str;
	int		i;

	cmds = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmds)
		return (NULL);
	cmd_str = NULL;
	i = 0;
	while (tokens)
	{
		if (tokens->com && tokens->com[0] != '\0')
			process_token(tokens, &cmd_str, cmds, &i);
		tokens = tokens->next;
	}
	if (cmd_str)
		cmds[i++] = cmd_str;
	cmds[i] = NULL;
	return (cmds);
}

/*
 * Searches `$PATH` for the full path to a given command.
 * Returns the first matching executable path, or NULL if not found.
 */
char	*get_path_in(char *cmd, t_shell *px)
{
	int		i;
	char	*full_path;
	char	**paths;

	i = 0;
	full_path = NULL;
	while (px->env_var[i] && strncmp(px->env_var[i], "PATH=", 5))
		i++;
	if (!px->env_var[i])
		return (NULL);
	paths = ft_split(px->env_var[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}
