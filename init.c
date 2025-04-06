/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/06 15:21:05 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//initial values
void	init_shell(t_shell *shell, char **envp)
{
	shell->exit = 0; //keep track on when to close.
	shell->env_var = copy_envp(envp);
	print_env(*shell); // test printing
}
void	take_comm(t_token *tokens)
{
	char	*command;

	command = readline("prompt> ");
	input(command, &tokens); //process string
}
