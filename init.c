/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/30 15:57:11 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//initial values
void	init_shell(t_shell *shell)
{
	shell->exit = 0; //keep track on when to close.
}
void	print_comm(t_token *tokens)
{
	char	*command;
	char	*path;
	pid_t	pid;
	char	*argv[] = {path, NULL};

	command = readline("prompt> ");
	//printf("command: %s\n", command); //test
	input(command, &tokens); //process string
	path = find_dir(tokens);
	printf("path: %s\n", path);
}
