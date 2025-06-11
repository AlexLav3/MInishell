/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/11 11:32:54 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_token		*token;

	printf("New minishell started!\n");
	(void)argv;
	token = NULL;
	if (argc > 1)
		return (printf("This program does not take any arguments\n"),
			EXIT_FAILURE);
	init_shell(&shell, envp);
	setup_shell_signals();
	if (!shell.exit)
		take_comm(&token, &shell);
	close_free(token, &shell);
	return (EXIT_SUCCESS);
}
