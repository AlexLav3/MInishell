/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:43:20 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/27 11:07:00 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				break;
			}
			tokens = tokens->next->next;
		}
		else
		{
			args[i++] = ft_strdup(tokens->com);
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
		close(cmd->redir_in);
	}
	if (cmd->redir_out != -1)
	{
		if (dup2(cmd->redir_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 redir_out");
			exit(EXIT_FAILURE);
		}
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
