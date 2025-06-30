#include "../Minishell.h"

// exc_pipes.c
void	execute_single_redir(t_cmd  *cmd, t_shell *shell)
{
	char	*path;
	int		status;

	status = 0;
	if (!cmd->args || !cmd->args[0] || cmd->redir_error)
		return ;
	path = get_cmd_path(cmd->args[0], shell);
	if (!path)
	{
		perror("Command not found utils.c redir");
		shell->exit_stat = 127;
		return ;
	}
	shell->pid1 = fork();
	if (shell->pid1 == -1)
	{
		perror("fork utils.c redir");
		shell->exit_stat = 1;
		if (path != cmd->args[0])
			free(path);
		return ;
	}
	else if (shell->pid1 == 0)
	{
		apply_redirection(cmd);
		execve(path, cmd->args, shell->env_var);
		perror("execve failed utils.c redir");
		shell->exit_stat = 127;
		exit(127); 
	}
	if (waitpid(shell->pid1, &status, 0) == -1)
	{
		perror("waitpid failed");
		shell->exit_stat = 1;
	}
	else if (WIFEXITED(status))
		shell->exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_stat = 128 + WTERMSIG(status);
	else
		shell->exit_stat = 1;
	if (path && path != cmd->args[0])
		free(path);
}

static void execve_cmd(t_cmd *cmd, t_shell *shell)
{
	int fd;

	// Apply input redirection if needed
	if (cmd->redir_in && cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->infile);
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2 infile");
			exit(1);
		}
		close(fd);
	}

	// Apply output redirection if needed
	if (cmd->redir_out && cmd->outfile)
	{
		fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(cmd->outfile);
			exit(1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 outfile");
			exit(1);
		}
		close(fd);
	}

	// Finally run the command
	char *full_path = get_cmd_path(cmd->args[0], shell);
	if (!full_path)
	{
		perror(cmd->args[0]);
		exit(127);
	}
	execve(full_path, cmd->args, shell->envp);
	perror("execve");
	free(full_path);
	exit(1);
}
 // similar to close_pipes_and_wait, needs to rework
static void close_all_pipe_fds(t_shell *px)
{
	if (px->pipe_fd[0] >= 0)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] >= 0)
		close(px->pipe_fd[1]);
	if (px->prev_fd[0] >= 0)
		close(px->prev_fd[0]);
	if (px->prev_fd[1] >= 0)
		close(px->prev_fd[1]);
}

void	execute_piped_commands(t_shell *px, t_cmd *cmds, 
			int cmd_count, t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(px->pipe_fd) == -1)
			pipex_error("pipe failed");

		px->pid = fork();
		if (px->pid == -1)
			pipex_error("fork failed");

		if (px->pid == 0) // child
		{
			// Setup input
			if (cmds[i].redir_in != -1)
			{
				if (dup2(cmds[i].redir_in, STDIN_FILENO) == -1)
					pipex_error("dup2 redir_in");
			}
			else if (i > 0)
			{
				if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
					pipex_error("dup2 prev_fd[0]");
			}

			// Setup output
			if (cmds[i].redir_out != -1)
			{
				if (dup2(cmds[i].redir_out, STDOUT_FILENO) == -1)
					pipex_error("dup2 redir_out");
			}
			else if (i < cmd_count - 1)
			{
				if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
					pipex_error("dup2 pipe_fd[1]");
			}

			// Close FDs
			close_all_pipe_fds(px); // check!!!!!

			execve_cmd(&cmds[i], shell); //check !!!!!!!!
			exit(127);
		}

		// Parent FD management
		if (px->prev_fd[0] != -1)
			close(px->prev_fd[0]);
		if (px->prev_fd[1] != -1)
			close(px->prev_fd[1]);

		px->prev_fd[0] = px->pipe_fd[0];
		px->prev_fd[1] = px->pipe_fd[1];
		px->pipe_fd[0] = -1;
		px->pipe_fd[1] = -1;
	}

	close_pipes_and_wait(px);
}
#include "../Minishell.h"

// parse_handle.c
void	fill_args_and_handle_redir(t_token *tokens, t_cmd *cmd, char **args, t_shell *shell)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (handle_redirection_token(tokens, cmd, shell))
		{
			if (!tokens->next)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				break ;
			}
			tokens = tokens->next->next;
		}
		else
		{
			if (!tokens->com)
			{
				tokens = tokens->next;
				continue;
			}
			args[i] = ft_strdup(tokens->com);
			if (!args[i])
			{
				ft_putendl_fd("minishell: memory allocation error", 2);
				while (--i >= 0)
					free(args[i]);
				args[0] = NULL;
				return;
			}
			i++;
			tokens = tokens->next;
		}
	}
	args[i] = NULL;
}

char	**parse_args_and_redirs(t_token *tokens, t_cmd *cmd, t_shell *shell)
{
	char	**args;
	int		arg_count;

	arg_count = count_args(tokens);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
	{
		reset_redirection(cmd);
		return (NULL);
	}
	fill_args_and_handle_redir(tokens, cmd, args, shell);
	return (args);
}

void	apply_redirection(t_cmd *cmd)
{
	if (cmd->redir_in != -1)
	{
		if (dup2(cmd->redir_in, STDIN_FILENO) == -1)
		{
			perror("dup2 redir_in");
			exit(EXIT_FAILURE);
		}
		if (cmd->redir_in > 2)
			close(cmd->redir_in);
	}
	if (cmd->redir_out != -1)
	{
		if (dup2(cmd->redir_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 redir_out");
			exit(EXIT_FAILURE);
		}
		if (cmd->redir_out > 2)
			close(cmd->redir_out);
	}
}

int	handle_redirection_token(t_token *tokens, t_cmd *cmd, t_shell *shell)
{
	if (cmd->redir_error)
		return (1);
	if (tokens->next == NULL)
		return (0);
	if (ft_strcmp(tokens->com, "<") == 0)
	{
		readirs(IN_FILE, cmd, tokens->next->com);
		return (1);
	}
	else if (ft_strcmp(tokens->com, ">") == 0)
	{
		readirs(OUT_FILE, cmd, tokens->next->com);
		return (1);
	}
	else if (ft_strcmp(tokens->com, ">>") == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strtrim(tokens->next->com, " \n\t");
		if (!cmd->outfile)
		{
			perror("ft_strtrim failed");
			cmd->redir_error = 1;
			return (1);
		}
		cmd->redir_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->redir_out < 0)
		{
			perror("redir: ");
			cmd->redir_error = 1;
		}
		return (1);
	}
	else if (ft_strcmp(tokens->com, "<<") == 0)
	{
		if (tokens->next && tokens->next->com)
		{
			heredoc_do(cmd, shell, tokens->next->com);
			return (1);
		}
	}
	return (0);
}

void	readirs(int dir, t_cmd *cmd, char *com)
{
	if (dir == IN_FILE)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strtrim(com, " \n\t");
		cmd->redir_in = open(cmd->infile, O_RDONLY);
		if (cmd->redir_in < 0)
		{
			perror("redir_in: ");
			cmd->redir_error = 1;
		}
	}
	else if (dir == OUT_FILE)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strtrim(com, " \n\t");
		cmd->redir_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (cmd->redir_out < 0)
		{
			perror("redir_out: ");
			cmd->redir_error = 1;
		}
	}
}
#include "../Minishell.h"

// // pipe_redir.c
void	strip_redirection_tokens(t_token **tokens)
{
	t_token *curr = *tokens;
	t_token *prev = NULL;
	t_token *to_free;

	while (curr && curr->next)
	{
		if (is_redir(curr->com))
		{
			// Remove redir token and next token (filename)
			to_free = curr;
			t_token *next_token = curr->next;

			if (prev)
				prev->next = next_token->next;
			else
				*tokens = next_token->next;

			curr = next_token->next;

			free(to_free->com);
			free(to_free);
			free(next_token->com);
			free(next_token);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	pipe_cmds_with_redir(char *command, t_token **tokens, t_shell *shell)
{
	t_shell	px;
	t_cmd	*cmds;
	char	**cmd_strs;
	int		cmd_count;
	int 	i;

	(void)command;
	cmd_strs = make_args_pipes(*tokens);
	if (!cmd_strs)
		return ;
	cmd_count = cmd_counter(cmd_strs);
	cmds = malloc(sizeof(t_cmd) * cmd_count);
	if (!cmds)
	{
		free_array(cmd_strs);
		return ;
	}
	i = -1;
	while (++i < cmd_count)
	{
		init_cmd(&cmds[i]); 
		t_token *subtokens = tokenize_command(cmd_strs[i]);
		if (!subtokens)
			continue;
		cmds[i].args = parse_args_and_redirs(subtokens, &cmds[i], shell);
		strip_redirection_tokens(&subtokens);
		deallocate(&subtokens);
	}
	init_pipex(&px, shell);
	execute_piped_commands(&px, cmds, cmd_count, shell);
	free_array(cmd_strs);

	i = -1;
	while (++i < cmd_count)
	{
		free_array(cmds[i].args);
		reset_redirection(&cmds[i]);
	}
	free(cmds);
}
#include <../Minishell.h>

// redir.c
void	heredoc_child_process(int write_fd, char *delimiter)
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
#include "../Minishell.h"

// redir_utils.c
int	is_redir(const char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0 || \
	ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
}

int	token_has_redir(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->com)
		{
			tokens = tokens->next;
			continue ;
		}
		if (ft_strcmp(tokens->com, "<") == 0 || \
			ft_strcmp(tokens->com, ">") == 0 || \
			ft_strcmp(tokens->com, ">>") == 0 || \
			ft_strcmp(tokens->com, "<<") == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
void	single_cmd_with_redir(char *command, t_token **tokens, t_shell *shell)
{
	t_cmd	cmd;

	init_cmd(&cmd);
	cmd.args = parse_args_and_redirs(*tokens, &cmd, shell);
	free(command);
	if (!cmd.args || !cmd.args[0] || cmd.redir_error)
	{
		if (cmd.args)
			free_array(cmd.args);
		reset_redirection(&cmd); // update 27 jun
		return ;
	}
	execute_single_redir(&cmd, shell);
	free_array(cmd.args);
	reset_redirection(&cmd);
}

void	reset_redirection(t_cmd *cmd)
{
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
	if (cmd->redir_in != -1)
	{
		close(cmd->redir_in);
		cmd->redir_in = -1;
	}
	if (cmd->redir_out != -1)
	{
		close(cmd->redir_out);
		cmd->redir_out = -1;
	}
}
