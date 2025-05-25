/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/25 20:20:01 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_token		*token;

	(void)argv;
	token = NULL;
	if (argc > 1)
		return (printf("This program does not take any arguments\n"),
				EXIT_FAILURE);
	init_shell(&shell, envp);
	setup_sig();
	if (!shell.exit)
		take_comm(&token, &shell);
	close_free(token, &shell);
	return (EXIT_SUCCESS);
}
