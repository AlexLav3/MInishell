/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:39:00 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/18 13:41:28 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>
static int token_is_redir(t_token *token)
{
	if (!token || !token->com)
		return 0;
	return (is_redir(token->com));
}

static int count_non_redir_tokens(t_token *tokens)
{
	int count = 0;

	while (tokens)
	{
		if (token_is_redir(tokens))
		{
			tokens = tokens->next; // skip redir operator
			if (tokens)
				tokens = tokens->next; // skip redir target
		}
		else
		{
			count++;
			tokens = tokens->next;
		}
	}
	return count;
}

static bool	handle_redirs_only(t_token *delim, t_cmd *cmd, t_shell *shell, t_token **tokens)
{
	t_token	*curr = delim;

	while (curr)
	{
		if (token_is_redir(curr))
		{
			if (handle_redirection_token(&curr, cmd, shell, tokens))
			{
				if (cmd->redir_error)
				{
					ft_putendl_fd("minishell: syntax error", 2);
					return false;
				}
				curr = curr->next->next;
				continue;
			}
		}
		curr = curr->next;
	}
	return true;
}

static bool	fill_args_only(t_token *tokens, char **args, t_cmd *cmd)
{
	t_token	*curr = tokens;
	int		i = 0;

	while (curr)
	{
		if (token_is_redir(curr))
		{
			// skip redir operator and target token
			curr = curr->next;
			if (curr)
				curr = curr->next;
			continue;
		}
		// else normal arg token
		if (handle_arg_token(&curr, args, &i) == -1)
		{
			while (--i >= 0)
				free(args[i]);
			free(args);
			cmd->args = NULL;
			return false;
		}
		i++;
		curr = curr->next;
	}
	args[i] = NULL;
	return true;
}

/*
 * Parses the command's tokens into arguments and handles redirection
 * tokens (e.g. `<`, `>`, `>>`, `<<`). Returns the final arguments array.
 * Sets redirection fields in the `t_cmd` struct.
 */
char	**parse_args_and_redirs(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	char	**args;
	int		arg_count;

	if (!handle_redirs_only(*tokens, cmd, shell, tokens))
		return NULL;

	arg_count = count_non_redir_tokens(*tokens);
	printf("arg_count; %d\n", arg_count);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
	{
		reset_redirection(cmd);
		close_free(tokens, shell);
		return (NULL);
	}
	// fill_args_and_handle_redir(tokens, cmd, args, shell);
	if (!fill_args_only(*tokens, args, cmd))
		return NULL;
	return (args);
}




/*
 * Checks the token type and handles redirection accordingly.
 * Delegates to appropriate functions for `<`, `>`, `>>`, or `<<`.
 * Returns 1 if it was a redirection token.
 */
int	handle_redirection_token(t_token **delim, t_cmd *cmd, t_shell *shell, t_token **tokens)
{
	
	if (!delim || !*delim || !cmd || !shell || !tokens)
		return (0);
	if (cmd->redir_error)
		return (1);
	if ((*delim)->next == NULL)
		return (0);
	if (ft_strcmp((*delim)->com, "<") == 0 || ft_strcmp((*delim)->com, ">") == 0)
		return (redir_token_in_out(delim, cmd));
	else if (ft_strcmp((*delim)->com, ">>") == 0)
		return (redir_token_append(delim, cmd));
	else if ((*delim)->com && ft_strcmp((*delim)->com, "<<") == 0)
	{
		if ((*delim)->next && (*delim)->next->com)
		{
			heredoc_do(cmd, shell, (*delim)->next->com, tokens);
			return (1);
		}
		else
		{
			ft_putendl_fd("minishell: syntax error near `<<`", 2);
			cmd->redir_error = 1;
			return (1);
		}
	}
	return (0);
}

/*
 * Iterates over tokens and fills the args array.
 * Skips redirection tokens using `handle_redirection_token`.
 * Adds normal command arguments using `handle_arg_token`.
//  */
// void	fill_args_and_handle_redir(t_token **tokens, t_cmd *cmd, char **args,
// 		t_shell *shell)
// {
// 	int	i;
// 	t_token	*curr;
	
// 	if (!tokens || !*tokens || !cmd || !shell)
// 		return;
	
// 	if (!args)
// 	{
// 		args[0] = NULL;
// 		return;
// 	}
// 	i = 0;
// 	curr = *tokens;
// 	while (curr)
// 	{
// 		if (handle_redirection_token(&curr, cmd, shell, tokens))
// 		{
// 			printf("handle_redirection_token loop\n");
// 			if (cmd->redir_error || !curr || !curr->next)
// 			{
// 				ft_putendl_fd("minishell: syntax error", 2);
// 				break ;
// 			}
// 			curr = curr->next->next;
// 		}
// 		else
// 		{
// 			if (handle_arg_token(&curr, args, &i) == -1)
// 			{
// 				printf("handle_arg_token loop\n");
// 				while (--i >= 0)
// 					free(args[i]);
// 				free(args);
// 				cmd->args = NULL;
// 				return ;
// 			}
// 			i++;
// 			curr = curr->next;
// 		}
// 	}
// 	args[i] = NULL;
// }
