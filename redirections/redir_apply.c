#include "../Minishell.h"

//redir_apply.c
static void	apply_in_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
		{
			perror("stdin redir");
			exit(EXIT_FAILURE);
		}
		if (fd > 2)
			close(fd);
	}
	else if (cmd->redir_in != -1)
	{
		if (dup2(cmd->redir_in, STDIN_FILENO) == -1)
		{
			perror("dup2 redir_in");
			exit(EXIT_FAILURE);
		}
		if (cmd->redir_in > 2)
			close(cmd->redir_in);
	}
}

static void	apply_out_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->outfile)
	{
		fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("stdout redir");
			exit(EXIT_FAILURE);
		}
		if (fd > 2)
			close(fd);
	}
	else if (cmd->redir_out != -1)
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

void	apply_redirection(t_cmd *cmd)
{
	if (cmd->redir_error)
		exit(EXIT_FAILURE);
	if (cmd->infile || cmd->redir_in != -1)
		apply_in_redirection(cmd);
	if (cmd->outfile || cmd->redir_out != -1)
		apply_out_redirection(cmd);
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
