/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/05 19:09:58 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


// temp stuff to test printing envp
static void print_env(t_token temp)
{
	if (!temp.envp)
	{
		printf("No environment variables.\n");
		return;
	}
	int i = 0;
	while (temp.envp[i] != NULL)
		printf("%s\n", temp.envp[i++]);
}
// temp stuff to test copy of envp
static char **copy_envp(char **envp)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (envp[count])
		count++;
	char **copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return NULL;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]); // allocate memory and copy the string, not just the address to ptr
		i++;
	}
	copy[count] = NULL;
	return copy;
}

int	main(int argc, char **argv, char **envp) // updated with envp
{
	t_shell shell;
	t_token	*token;

	// t_token temp; //temp for envp
	// temp.envp = copy_envp(envp); // needs to create a copy so we can change and free them later
	// print_env(temp); // test printing

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