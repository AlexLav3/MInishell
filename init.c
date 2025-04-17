/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:36:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/17 14:00:03 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//initial values
void	init_shell(t_shell *shell, char **envp)
{
	shell->exit = 0;
	shell->env_var = copy_envp(envp);
	if (!shell->env_var)
	{
		perror("Failed to copy envp");
		exit(EXIT_FAILURE); // or however we need to handle it later
	}
	shell->pwd = set_pwd(shell);
}

void	take_comm(t_token **tokens, t_shell *shell)
{
	char	*command;

	while (1)
	{
		command = readline("prompt> ");
		if (!command)
		{
			deallocate(tokens);
			pipex_error("exit");
		}
		if (ft_strlen(command) > 0 && !(command[0] == ' ' && command[1] != ' '))
			add_history(command);
		if (check_for_exit(command))
			break ;
		input(command, tokens);
		process_commands(command, tokens, shell);
	}
	rl_clear_history();
}

char	*set_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0); // the buffer needs to be freed - added to clean exit
	if (cwd == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}
