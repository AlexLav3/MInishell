#include <../Minishell.h>

//parser_redir_utils.c
int	redir_token_in_out(t_token *tokens, t_cmd *cmd)
{
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
	return (0);
}

int	redir_token_append(t_token *tokens, t_cmd *cmd)
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
	cmd->redir_out = open(cmd->outfile,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->redir_out < 0)
	{
		perror("redir: ");
		cmd->redir_error = 1;
	}
	return (1);
}

int	handle_arg_token(t_token *token, char **args, int *i)
{
	if (!token->com)
		return (0);
	args[*i] = ft_strdup(token->com);
	if (!args[*i])
	{
		ft_putendl_fd("memory allocation error", 2);
		while (--(*i) >= 0)
			free(args[*i]);
		args[0] = NULL;
		return (-1);
	}
	return (1);
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