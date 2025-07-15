/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:39:00 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/15 21:43:18 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

/*
 * Parses the command's tokens into arguments and handles redirection
 * tokens (e.g. `<`, `>`, `>>`, `<<`). Returns the final arguments array.
 * Sets redirection fields in the `t_cmd` struct.
 */
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

/*
 * Checks the token type and handles redirection accordingly.
 * Delegates to appropriate functions for `<`, `>`, `>>`, or `<<`.
 * Returns 1 if it was a redirection token.
 */
int	handle_redirection_token(t_token *tokens, t_cmd *cmd, t_shell *shell)
{
	if (cmd->redir_error)
		return (1);
	if (tokens->next == NULL)
		return (0);
	if (ft_strcmp(tokens->com, "<") == 0 || ft_strcmp(tokens->com, ">") == 0)
		return (redir_token_in_out(tokens, cmd));
	else if (ft_strcmp(tokens->com, ">>") == 0)
		return (redir_token_append(tokens, cmd));
	else if (ft_strcmp(tokens->com, "<<") == 0)
	{
		if (tokens->next && tokens->next->com)
		{
			heredoc_do(cmd, shell, tokens->next->com, tokens);
			return (1);
		}
	}
	return (0);
}

/*
 * Iterates over tokens and fills the args array.
 * Skips redirection tokens using `handle_redirection_token`.
 * Adds normal command arguments using `handle_arg_token`.
 */
void	fill_args_and_handle_redir(t_token *tokens, t_cmd *cmd, char **args,
		t_shell *shell)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (handle_redirection_token(tokens, cmd, shell))
		{
			if (!tokens->next)
			{
				ft_putendl_fd("minishell: syntax error", 2);
				break ;
			}
			tokens = tokens->next->next;
		}
		else
		{
			if (handle_arg_token(tokens, args, &i) == -1)
				return ;
			i++;
			tokens = tokens->next;
		}
	}
	args[i] = NULL;
}
