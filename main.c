/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/06 11:30:29 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int argc, char **argv, char **envp) // updated with envp
{
	t_shell shell;
	t_token	*token;

	(void)argv;
	t_token env_clone; //env_clone for envp
	env_clone.envp = copy_envp(envp); // needs to create a copy so we can change and free them later
	// print_env(env_clone); // test printing

	token = malloc(sizeof(t_token));
	if (argc > 1)
		return (printf("This program does not take any arguments\n"),
				EXIT_FAILURE);
	init_shell(&shell);	
	while (!shell.exit)
	{
		//handle input
		print_comm(token);
		//find command
		//execute
	}
	return (EXIT_SUCCESS);
}
