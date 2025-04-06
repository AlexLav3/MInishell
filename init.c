/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/06 20:13:56 by elavrich         ###   ########.fr       */
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
void	take_comm(t_token *tokens)
{
	char	*command;
	char	**cmd;

	command = readline("prompt> ");
	input(command, &tokens); 
	cmd = make_args(tokens);
	//int j = 0;
	// while (cmd[j]) //testing 
	// {
	// 	printf("arg[%d] = %s\n", j, cmd[j]); //once the comm is executed, or  not found, we should free the array cmd.
	// 	j++;
	// }
}
