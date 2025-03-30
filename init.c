/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/30 16:27:21 by elavrich         ###   ########.fr       */
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
	//printf("command: %s\n", command); //test to see initial string
	input(command, &tokens); //process string
	path = find_dir(tokens);
	printf("path: %s\n", path); //test to see what path returns. 
	//path keeps being printed once found even if later you put random words, even if you free it path
	//find why and free it. it should not print the path if the command isn't found.
}
