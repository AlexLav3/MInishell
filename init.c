/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/07 14:45:08 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//initial values
void	init_shell(t_shell *shell, char **envp)
{
	shell->exit = 0; //keep track on when to close.env
	shell->env_var = copy_envp(envp);
	// print_env(*shell); // test printing
}
// f:07/04/25 - we will need more space for sep
void	child_process(t_shell *shell, char **cmd, char *path)
{
	if (execve(path, cmd, shell->env_var) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}
void	execute_cmd(char **cmd, t_shell *shell)
{
	char	*path;
	pid_t	pid;

	path = get_cmd_path(cmd[0], shell);
	if (!path)
	{
		perror("Command not found");
		return;
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
		child_process(shell, cmd, path);
	else
		waitpid(pid, NULL, 0);
	free(path);
}

void	take_comm(t_token *tokens, t_shell *shell)
{
	char	*command;
	char	**cmd;
	pid_t	pid;

	while (1)
	{
		command = readline("prompt> ");
		if (!command) // f:07/04/25 - ctrl - d - otherwise runs to seg fault, we need to handle this later
		{
			free(command);
			break;
		}
		if (command && *command)
			add_history(command);
		
		if (ft_strcmp(command, "exit") == 0) {
			free(command);
			break;  // Exit the loop if user types "exit"
		}
		input(command, &tokens);
		cmd = make_args(tokens);
		free(command);
		if (!cmd) {
			deallocate(&tokens);
			continue;
		}
		execute_cmd(cmd, shell);
		free_array(cmd);
		deallocate(&tokens);
	}
	rl_clear_history();
}
