/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:39:08 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/23 17:11:42 by ferenc           ###   ########.fr       */
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
int	count_pipes(t_token *tokens)
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
static int	process_pipe_token(t_pipe_context *ctx, t_grouped group)
{
	ctx->cmd->args = parse_args_and_redirs(ctx->start, ctx->cmd, group);
	if (!ctx->cmd->args)
		return (0);
	if (ctx->curr)
		*(ctx->start) = ctx->curr->next;
	else
		*(ctx->start) = NULL;
	return (1);
}

static int	handle_last_command(t_grouped group, t_pipe_context *ctx, int cmd_i)
{
	if (cmd_i < group->cmd_count && *(ctx->start))
	{
		group->cmds[cmd_i].args = parse_args_and_redirs(
				ctx->start, &group->cmds[cmd_i], group);
		if (!group->cmds[cmd_i].args)
			return (0);
	}
	return (1);
}

/* Builds an array of commands (cmds) from a linked list 
 of tokens split by pipes.
 Iterates through tokens and processes each segment separated by pipe tokens.
 For each pipe token encountered,
 extracts and parses the corresponding command arguments and redirections.
 After processing all pipes, parses the remaining tokens as the last command.
 Stops processing if tokens are exhausted or all commands have been built.
 */
static int	build_cmds_from_tokens(t_grouped group)
{
	int				cmd_i;
	t_pipe_context	ctx;

	cmd_i = 0;
	ctx.start = group->tokens;
	ctx.prev = NULL;
	ctx.curr = *(group->tokens);
	if (!group->tokens || group->cmd_count == 0)
		return (0);
	while (ctx.curr && cmd_i < group->cmd_count)
	{
		if (ctx.curr->com && ft_strcmp(ctx.curr->com, "|") == 0)
		{
			ctx.cmd = &(group->cmds[cmd_i]);
			if (!process_pipe_token(&ctx, group))
				return (0);
			cmd_i++;
		}
		ctx.prev = ctx.curr;
		ctx.curr = ctx.curr->next;
	}
	return (handle_last_command(group, &ctx, cmd_i));
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
	int			cmd_count;
	t_cmd		*cmds;
	t_shell		px;
	t_token		*head;
	t_grouped	group;

	head = *tokens;
	cmd_count = init_cmds_and_group(tokens, shell, &cmds, &group);
	if (!cmd_count || !build_cmds_from_tokens(group))
		return (free(group), handle_cmd_failure(cmds, tokens, shell,
				cmd_count));
	init_pipex(&px, shell);
	execute_piped_commands(&px, group);
	cleanup_pipe_cmds(cmds, cmd_count, tokens, head);
	free(group);
}
