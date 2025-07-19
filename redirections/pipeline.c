/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:39:08 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/19 21:18:13 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

/* Counts the number of commands separated by pipe tokens
 ("|") in a linked list of tokens.
 * Returns 0 if the token list is empty.
 * Starts counting from 1 since at least one 
  command exists if tokens are present.
 * Iterates through the tokens, incrementing
  count each time a pipe token is found.
 */
static int	count_pipes(t_token *tokens)
{
	int	count;

	if (!tokens)
		return (0);
	count = 1;
	while (tokens)
	{
		if (tokens->com && ft_strcmp(tokens->com, "|") == 0)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

/* Processes a pipe token within the current parsing context.
 Temporarily disconnects the previous token 
 from the current to isolate the command segment.
 Parses the arguments and redirections 
 for the isolated command segment and stores them in ctx->cmd->args.
 Restores the original linked list connections.
 Advances the start pointer to the token after the current command.
 */
static void	process_pipe_token(t_pipe_context *ctx, t_shell *shell)
{
	if (ctx->prev)
		ctx->prev->next = NULL;
	ctx->cmd->args = parse_args_and_redirs(ctx->start, ctx->cmd, shell);
	if (ctx->prev)
		ctx->prev->next = ctx->curr;
	*(ctx->start) = ctx->curr->next;
}

/* Builds an array of commands (cmds) from a linked list 
 of tokens split by pipes.
 Iterates through tokens and processes each segment separated by pipe tokens.
 For each pipe token encountered,
 extracts and parses the corresponding command arguments and redirections.
 After processing all pipes, parses the remaining tokens as the last command.
 Stops processing if tokens are exhausted or all commands have been built.
 */
static void	build_cmds_from_tokens(t_token **tokens, t_cmd *cmds, int cmd_count,
		t_shell *shell)
{
	int				cmd_i;
	t_pipe_context	ctx;

	cmd_i = 0;
	ctx.start = tokens;
	ctx.prev = NULL;
	ctx.curr = *tokens;
	if (!tokens || cmd_count == 0)
		return ;
	while (ctx.curr && cmd_i < cmd_count)
	{
		if (ctx.curr->com && ft_strcmp(ctx.curr->com, "|") == 0)
		{
			ctx.cmd = &cmds[cmd_i];
			process_pipe_token(&ctx, shell);
			cmd_i++;
		}
		ctx.prev = ctx.curr;
		ctx.curr = ctx.curr->next;
	}
	if (cmd_i < cmd_count && *(ctx.start))
		cmds[cmd_i].args = parse_args_and_redirs(ctx.start, &cmds[cmd_i],
				shell);
}

/*
  Main function to handle piped commands with redirections.
  Counts how many commands are separated by pipes.
  Allocates and initializes an array of t_cmd structures for each command.
  Parses tokens into commands and arguments using build_cmds_from_tokens.
  Initializes the pipe execution context.
  Executes all commands in a pipeline.
  Cleans up allocated resources: frees command arguments arrays 
  and resets redirections,
  then frees the commands array.*/
void	pipe_cmds_with_redir(t_token **tokens, t_shell *shell)
{
	int		cmd_count;
	t_cmd	*cmds;
	t_shell	px;
	int		i;
	t_token	*head;

	head = *tokens;
	cmd_count = count_pipes(*tokens);
	cmds = malloc(sizeof(t_cmd) * cmd_count);
	if (!cmds)
		return ;
	i = 0;
	while (i < cmd_count)
		init_cmd(&cmds[i++]);
	build_cmds_from_tokens(tokens, cmds, cmd_count, shell);
	init_pipex(&px, shell);
	execute_piped_commands(&px, cmds, cmd_count, shell, tokens);
	i = 0;
	while (i < cmd_count)
	{
		free_array(cmds[i].args);
		reset_redirection(&cmds[i]);
		i++;
	}
	free(cmds);
	deallocate(&head);
	*tokens = NULL;
}
