/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/11 18:14:49 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//initial values
void	init_pipex(t_shell *px, t_shell *shell)
{
	px->envp = shell->env_var;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->exit = 0;
	shell->exit_stat = 0;
	shell->redir_in = -1;
	shell->redir_out = -1;
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
		signal(SIGINT, handle_sigint_prompt);
		signal(SIGQUIT, SIG_IGN);
		command = readline("prompt> ");
		if (!command)
		{
			deallocate(tokens);
			pipex_error("exit");
		}
		if (ft_strlen(command) > 0)
			add_history(command);
		if (input(command, tokens, shell) < 0)
			deallocate(tokens);
		process_commands(command, tokens, shell);
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
		return (NULL);
	}
	return (cwd);
}
