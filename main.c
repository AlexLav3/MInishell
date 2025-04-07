/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/07 15:15:16 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_token	*token;

	(void)argv;
	// // token = malloc(sizeof(t_token));
	// if (!token) // f:07/04/25 - due to malloc
	// 	return 1;
	token = NULL;
	if (argc > 1)
		return (printf("This program does not take any arguments\n"),
				EXIT_FAILURE);
	init_shell(&shell, envp);
	if (!shell.exit)
		take_comm(&token, &shell);
	deallocate(token); // f:07/04/25 - free tokens, we may need to free shell as well
	return (EXIT_SUCCESS);
}
