/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:43:20 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 06:51:05 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

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

	shell->redir_in = -1;
	shell->redir_out = -1;
	shell->infile = NULL;
	shell->outfile = NULL;
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
