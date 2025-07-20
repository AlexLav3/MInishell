/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:39:08 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/20 09:07:02 by ferenc           ###   ########.fr       */
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
static int	process_pipe_token(t_pipe_context *ctx, t_shell *shell)
{
	if (ctx->prev)
		ctx->prev->next = NULL;
	ctx->cmd->args = parse_args_and_redirs(ctx->start, ctx->cmd, shell);
	if (!ctx->cmd->args)
	{
		if (ctx->prev)
			ctx->prev->next = ctx->curr;
		return (0); // failure
	}
	if (ctx->prev)
		ctx->prev->next = ctx->curr;
	*(ctx->start) = ctx->curr->next;
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
static int	build_cmds_from_tokens(t_grouped *grp)
{
	int				cmd_i;
	t_pipe_context	ctx;

	cmd_i = 0;
	ctx.start = grp->tokens;;
	ctx.prev = NULL;
	ctx.curr = *(grp->tokens);
	if (!grp->tokens || grp->cmd_count == 0)
		return (0);
	while (ctx.curr && cmd_i < grp->cmd_count)
	{
		if (ctx.curr->com && ft_strcmp(ctx.curr->com, "|") == 0)
		{
			ctx.cmd = &(grp->cmds[cmd_i]);
			if (!process_pipe_token(&ctx, grp->shell))
				return 0;
			cmd_i++;
		}
		ctx.prev = ctx.curr;
		ctx.curr = ctx.curr->next;
	}
	if (cmd_i < grp->cmd_count && *(ctx.start))
	{
		grp->cmds[cmd_i].args = parse_args_and_redirs(ctx.start, &grp->cmds[cmd_i],
			grp->shell);
		if (!grp->cmds[cmd_i].args)
			return 0;
	}
	return 1;
}

static t_grouped build_group(t_shell *shell, t_cmd *cmds, int cmd_count, t_token **tokens)
{
	t_grouped group;

	group.tokens = tokens;
	group.shell = shell;
	group.cmds = cmds;
	group.cmd_count = cmd_count;
	return group;
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
	int			i;
	t_token 	*head;
	t_grouped   grp;

	head = *tokens; 
	cmd_count = count_pipes(*tokens);
	cmds = malloc(sizeof(t_cmd) * cmd_count);
	if (!cmds)
		return ;
	i = 0;
	while (i < cmd_count)
		init_cmd(&cmds[i++]);
	grp = build_group(shell, cmds, cmd_count, tokens);
	if (!build_cmds_from_tokens(&grp)) // update
	{
		free(cmds);
		deallocate(tokens);
		*tokens = NULL;
		shell->exit_stat = 1;
		return; // or propagate error code
	}
	init_pipex(&px, shell);
	execute_piped_commands(&px, &grp); // update
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
