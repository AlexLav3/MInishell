/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:07:11 by ferenc            #+#    #+#             */
/*   Updated: 2025/05/01 15:34:35 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	handle_first_redir_child(t_shell *shell, t_shell *px, char *cmd)
{
	if (shell->redir_in != -1)
	{
		if (dup2(shell->redir_in, STDIN_FILENO) == -1)
			pipex_error("dup2 redir_in");
		close(shell->redir_in);
	}
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 pipe out");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
}

void	handle_last_redir_child(t_shell *shell, t_shell *px, char *cmd)
{
	if (dup2(px->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 pipe in");
	if (shell->redir_out != -1)
	{
		if (dup2(shell->redir_out, STDOUT_FILENO) == -1)
			pipex_error("dup2 redir_out");
		close(shell->redir_out);
	}
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, px);
}

void	strip_redirection_tokens(t_token **tokens)
{
	t_token	*tmp = *tokens;
	t_token	*prev = NULL;
	t_token	*next;

	while (tmp)
	{
		if (is_redir(tmp->com) && tmp->next)
		{
			next = tmp->next->next;
			if (prev)
				prev->next = next;
			else
				*tokens = next;
			free(tmp->next->com);
			free(tmp->next);
			free(tmp->com);
			free(tmp);
			tmp = next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	init_pipex(t_shell *px, t_shell *shell)
{
	px->envp = shell->env_var;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
}

void	execute_piped_commands(t_shell *px, char **cmds, int cmd_count, t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(px->pipe_fd) == -1)
			pipex_error("pipe failed");
		px->pid = fork();
		if (px->pid == -1)
			pipex_error("fork failed");
		if (px->pid == 0)
		{
			if (i == 0)
				handle_first_redir_child(shell, px, cmds[i]);
			else if (i == cmd_count - 1)
				handle_last_redir_child(shell, px, cmds[i]);
			else
				middle_child_process(px, cmds[i]);
			exit(0);
		}
		fd_handle(i, cmd_count, px);
	}
	close_pipes_and_wait(px);
}

void	pipe_cmds_with_redir(char *command, t_token **tokens, t_shell *shell)
{
	t_shell	px;
	char	**cmds;
	int		cmd_count;
	char 	**args;

	args = parse_args_and_redirs(*tokens, shell);
	strip_redirection_tokens(tokens);
	cmds = make_args_pipes(*tokens);
	if (!cmds)
		return ;
	cmd_count = cmd_counter(cmds);
	init_pipex(&px, shell);
	execute_piped_commands(&px, cmds, cmd_count, shell);
	free_array(cmds);
	free_array(args);
	reset_redirection(shell);
}
