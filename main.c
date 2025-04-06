/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/06 15:05:32 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int argc, char **argv, char **envp) // updated with envp
{
	t_shell shell;
	t_token	*token;

	(void)argv;
	shell.env_var = copy_envp(envp); // needs to create a copy so we can change and free them later
	print_env(shell); // test printing

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
