/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:43:20 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/26 12:21:41 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	fill_args_and_handle_redir(t_token *tokens, t_shell *shell, char **args)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (handle_redirection_token(tokens, shell))
			tokens = tokens->next;
		else
			args[i++] = ft_strdup(tokens->com);
		tokens = tokens->next;
	}
	args[i] = NULL;
}

char	**parse_args_and_redirs(t_token *tokens, t_shell *shell)
{
	char	**args;
	int		arg_count;

	// shell->redir_in = -1;
	// shell->redir_out = -1;
	// shell->infile = NULL;
	// shell->outfile = NULL; //moved to initial values, feel free to uncommend them here if creates issues. 
	// otherwise, remove from here.
	arg_count = count_args(tokens);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	fill_args_and_handle_redir(tokens, shell, args);
	return (args);
}

void	apply_redirection(t_shell *shell)
{
	if (shell->redir_in != -1)
	{
		if (dup2(shell->redir_in, STDIN_FILENO) == -1)
		{
			perror("dup2 redir_in");
			exit(EXIT_FAILURE);
		}
		close(shell->redir_in);
	}
	if (shell->redir_out != -1)
	{
		if (dup2(shell->redir_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 redir_out");
			exit(EXIT_FAILURE);
		}
		close(shell->redir_out);
	}
}

int	handle_redirection_token(t_token *tokens, t_shell *shell)
{
	if (ft_strcmp(tokens->com, "<") == 0 && tokens->next)
		return (readirs(1, shell, tokens->next->com), 1);
	else if (ft_strcmp(tokens->com, ">") == 0 && tokens->next)
		return (readirs(2, shell, tokens->next->com), 1);
	else if (ft_strcmp(tokens->com, ">>") == 0 && tokens->next)
	{
		shell->outfile = ft_strtrim(tokens->next->com, " \n\t");
		shell->redir_out = open(shell->outfile, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (shell->redir_out < 0)
			perror("redir: ");
		return (1);
	}
	else if (ft_strcmp(tokens->com, "<<") == 0 && tokens->next->com)
		return (heredoc_do(shell, tokens->next->com), 1);
	return (0);
}

void	readirs(int dir, t_shell *shell, char *com)
{
	if (dir == IN_FILE)
	{
		shell->infile = ft_strtrim(com, " \n\t");
		shell->redir_in = open(shell->infile, O_RDONLY);
		if (shell->redir_in < 0)
			perror("redir: ");
	}
	else if (dir == OUT_FILE)
	{
		shell->outfile = ft_strtrim(com, " \n\t");
		shell->redir_out = open(shell->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (shell->redir_out < 0)
			perror("redir: ");
	}
}
