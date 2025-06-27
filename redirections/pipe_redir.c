/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:07:11 by ferenc            #+#    #+#             */
/*   Updated: 2025/06/27 12:01:52 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// pipe_redir.c
void	middle_child_process_redir(t_cmd *cmd, t_shell *px, char *cmd_str)
{
	if (cmd->redir_error)
		exit(1);


	if (cmd->redir_in != -1)
	{
		if (dup2(cmd->redir_in, STDIN_FILENO) == -1)
			pipex_error("dup2 redir_in");
		close(cmd->redir_in);
	}
	else if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 prev pipe in");

	if (cmd->redir_out != -1)
	{
		if (dup2(cmd->redir_out, STDOUT_FILENO) == -1)
			pipex_error("dup2 redir_out");
		close(cmd->redir_out);
	}
	else if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 pipe out");

	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	if (px->prev_fd[0] >= 0)
		close(px->prev_fd[0]);
	if (px->prev_fd[1] >= 0)
		close(px->prev_fd[1]);

	execute_cmd(cmd_str, px);
}

void	handle_first_redir_child(t_cmd *cmd, t_shell *px, char *cmd_str)
{
	if (cmd->redir_error)
		exit(1);
	if (cmd->redir_in != -1)
	{
		if (dup2(cmd->redir_in, STDIN_FILENO) == -1)
			pipex_error("dup2 redir_in");
		close(cmd->redir_in);
	}
	if (cmd->redir_out != -1)
	{
		if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
			pipex_error("dup2 pipe out");
		close(cmd->redir_out);
	}
	else
	{
		if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
			pipex_error("dup2 pipe out");
	}
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd_str, px);
}

void	handle_last_redir_child(t_cmd *cmd, t_shell *px, char *cmd_str)
{
	if (cmd->redir_error)
		exit(1);

	if (cmd->redir_in != -1)
	{
		if (dup2(cmd->redir_in, STDIN_FILENO) == -1)
			pipex_error("dup2 redir_in");
		close(cmd->redir_in);
	}
	else if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 prev pipe in");

	if (cmd->redir_out != -1)
	{
		if (dup2(cmd->redir_out, STDOUT_FILENO) == -1)
			pipex_error("dup2 redir_out");
		close(cmd->redir_out);
	}

	if (px->prev_fd[0] >= 0)
		close(px->prev_fd[0]);
	if (px->prev_fd[1] >= 0)
		close(px->prev_fd[1]);
	execute_cmd(cmd_str, px);
}

void	strip_redirection_tokens(t_token **tokens)
{
	t_token	*curr = *tokens;
	t_token	*prev = NULL;
	t_token	*next;

	while (curr && curr->next)
	{
		if (is_redir(curr->com))
		{
			next = curr->next->next;
			free(curr->com);
			free(curr->next->com);
			free(curr->next);
			free(curr);

			if (prev)
				prev->next = next;
			else
				*tokens = next;

			curr = next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	pipe_cmds_with_redir(char *command, t_token **tokens, t_shell *shell)
{
	t_shell	px;
	t_cmd	cmd;
	char	**cmds;
	int		cmd_count;

	(void)command;
	init_cmd(&cmd); 
	cmd.args = parse_args_and_redirs(*tokens, &cmd, shell);
	strip_redirection_tokens(tokens);
	cmds = make_args_pipes(*tokens);
	if (!cmds)
		return ;
	cmd_count = cmd_counter(cmds);
	init_pipex(&px, shell);
	execute_piped_commands(&px, cmds, cmd_count, shell);
	free_array(cmds);
	free_array(cmd.args);
	reset_redirection(&cmd);
}
