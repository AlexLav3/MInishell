/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/19 21:29:02 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	init_pipex(t_shell *px, t_shell *shell)
{
	*px = *shell;
	px->env_var = shell->env_var;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
	px->prev_fd[0] = -1;
	px->prev_fd[1] = -1;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->redir_in = -1;
	cmd->redir_out = -1;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->args = NULL;
	cmd->redir_error = 0;
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->exit = 0;
	shell->exit_stat = 0;
	shell->infile = NULL;
	shell->outfile = NULL;
	shell->env_var = copy_envp(envp, NULL);
	if (!shell->env_var)
	{
		perror("Failed to copy envp");
		exit(EXIT_FAILURE);
	}
	shell->pwd = set_pwd(shell);
}

void	take_comm(t_token **tokens, t_shell *shell)
{
	char	*command;

	while (!shell->exit)
	{
		command = readline("prompt> ");
		if (!command)
		{
			close_free(tokens, shell);
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (ft_strlen(command) > 0)
			add_history(command);
		if (input(command, tokens, shell) < 0)
		{
			free(command);
			deallocate(tokens);
			continue ;
		}
		if (syntax_error(tokens, shell) == 0)
			process_commands(tokens, shell);
		deallocate(tokens);
		free(command);
	}
	rl_clear_history();
}

char	*set_pwd(t_shell *shell)
{
	char	*cwd;

	(void)shell;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		free(cwd);
		return (NULL);
	}
	return (cwd);
}
