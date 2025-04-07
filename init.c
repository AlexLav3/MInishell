/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/07 10:42:19 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//initial values
void	init_shell(t_shell *shell, char **envp)
{
	shell->exit = 0; //keep track on when to close.
	shell->env_var = copy_envp(envp);
	//print_env(*shell); // test printing
}
void	take_comm(t_token *tokens, t_shell *shell)
{
	char	*command;
	char	**cmd;
	char	*path;

	command = readline("prompt> ");
	if (!command) // f:07/04/25 - ctrl - d - otherwise runs to seg fault, we need to handle this later
		return;
	input(command, &tokens);
	cmd = make_args(tokens);
	if(cmd) //basic version, will prob need to change later.
	{
		path = get_cmd_path(cmd[0], shell);
		if (!path)
			free_array(cmd);
		else 
		{
			if(execve(path, cmd, shell->env_var) == -1)
				free_array(cmd);
		}
		
	}
	//int j = 0;//testing 
	// while (cmd[j]) 
	// {
	// 	printf("arg[%d] = %s\n", j, cmd[j]); //once the comm is executed, or  not found, we should free the array cmd.
	// 	j++;
	// }
}
