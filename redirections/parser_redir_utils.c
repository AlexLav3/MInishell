/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:38:35 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/20 23:22:30 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

/*
 * Opens input or output files based on `<` or `>` token.
 * Updates the corresponding file descriptors in `t_cmd`.
 */
int	redir_token_in_out(t_token **tokens, t_cmd *cmd)
{
	if (ft_strcmp((*tokens)->com, "<") == 0)
	{
		readirs(IN_FILE, cmd, (*tokens)->next->com);
		return (1);
	}
	else if (ft_strcmp((*tokens)->com, ">") == 0)
	{
		readirs(OUT_FILE, cmd, (*tokens)->next->com);
		return (1);
	}
	return (0);
}

/*
 * Handles the `>>` token for append redirection.
 * Opens the output file in append mode.
 * Sets `redir_out` and marks error if the file cannot be opened.
 */
int	redir_token_append(t_token **tokens, t_cmd *cmd)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strtrim((*tokens)->next->com, " \n\t");
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

/*
 * Copies a token into the args array.
 * Handles memory allocation errors and cleanup.
 */
int	handle_arg_token(t_token **token, char **args, int *i)
{
	if (!(*token)->com)
		return (0);
	args[*i] = ft_strdup((*token)->com);
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

/*
 * Generic helper for input (`<`) or output (`>`) redirection.
 * Trims whitespace, opens file with appropriate flags, stores path,
 * and updates `redir_in` or `redir_out`. Marks errors on failure.
 */
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
			perror("redir_in");
			cmd->redir_error = 1;
		}
	}
	else if (dir == OUT_FILE)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strtrim(com, " \n\t");
		cmd->redir_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->redir_out < 0)
		{
			perror("redir_out");
			cmd->redir_error = 1;
		}
	}
}
