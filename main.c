/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/29 00:00:39 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	main(int argc, char **argv)
{
	t_shell shell;
	if (argc > 1)
		return (printf("This program does not take any arguments\n"),
			EXIT_FAILURE);
	init_shell(&shell);
	//honestly, not sure if while loop is needed, but it makes sense. (otherwise, it would just return)
	while (!shell.exit)
	{
		//handle input
		//process string
		//find command
		//execute
	}
	return (EXIT_SUCCESS);
}