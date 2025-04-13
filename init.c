/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/13 03:02:02 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//initial values
void	init_shell(t_shell *shell, char **envp)
{
	shell->exit = 0;
	shell->env_var = copy_envp(envp);
}

void	execute_single_cmd(char **cmd, t_shell *shell)
{
	char	*path;

	if (!cmd[0] || !cmd)
		return ;
	
	path = get_cmd_path(cmd[0], shell);
	if (!path)
	{
		perror("Command not found"); 
		return ;
	}
	shell->pid1 = fork();
	if (shell->pid1 == -1)
		perror("fork");
	else if (shell->pid1 == 0)
	{
		if (execve(path, cmd, shell->env_var) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(shell->pid1, NULL, 0);
	free(path);
}

void	process_commands(char *command, t_token **tokens, t_shell *shell)
{
	char	**cmd;

	cmd = make_args(*tokens);
	free(command);
	if (!cmd)
	{
		deallocate(tokens);
		return ;
	}
	if (handle_builtin(cmd, shell))
	{
		free_array(cmd);
		deallocate(tokens);
		return ;
	}
	if (has_seps(cmd, '|')) // command with pipe(s)
	{
		split_by_pipe(shell, cmd);
		execute_pipeline(shell);
	}
	else
		execute_single_cmd(cmd, shell); //single command - echo works with this already. 
	free_array(cmd);
	deallocate(tokens);
}

void	take_comm(t_token **tokens, t_shell *shell)
{
	char	*command;	

	while (1)
	{
		command = readline("prompt> ");
		if (!command)
		{
			deallocate(tokens);
			break ;
		}
		if (command && *command)
			add_history(command);
		if (check_for_exit(command))
			break ;
		input(command, tokens);
		process_commands(command, tokens, shell);
	}
	rl_clear_history();
}
