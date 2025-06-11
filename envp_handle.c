/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:53:36 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/11 14:34:52 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	print_env(t_shell shell)
{
	int	i;

	if (!shell.env_var)
	{
		printf("No environment variables.\n");
		return ;
	}
	i = 0;
	while (shell.env_var[i] != NULL)
		printf("%s\n", shell.env_var[i++]);
}

/*
ahh, the trick I mentioned you on slack:
	So, as you mentioned yesterday copy_envp, I decided to go back to it. But it required a bit of modification due to the leak,
	and also because we use it in the init.c function.
	Now the copy_envp can copy env in the init, but also be used if there is a new_var.
	We call it with NULL in init, shell->env_var = copy_envp(envp, NULL);
	or with the new variable in add_env, new_envp = copy_envp(shell->env_var, var);
	A fast test showed no leaks, but I will test it again later once I finish with the rest of Norminette.
	I created a helper function called copy_env_vars and placed it in utils2.c.
	This actually makes the copy from envp to copy. While the copy_envp function handles the new variable after that, and added to the end.
*/
char	**copy_envp(char **envp, char *new_var)
{
	int		count;
	char	**copy;

	count = 0;
	while (envp[count])
		count++;								//pls tell me what you're trying to do with this check (below this line)
	copy = malloc(sizeof(char *) * (count + 1 + (new_var != NULL)));
	if (!copy)
		return (NULL);
	if (!copy_env_vars(copy, envp, count))
		return (free(copy), NULL);
	if (new_var)
	{
		copy[count] = ft_strdup(new_var);
		if (!copy[count])
		{
			while (count-- > 0)
				free(copy[count]);
			return (free(copy), NULL);
		}
	}			//here too
	copy[count + (new_var != NULL)] = NULL;
	return (copy);
}

void	add_env(t_shell *shell, char *var)
{
	char	**new_envp;
	int		i;

	new_envp = copy_envp(shell->env_var, var);
	if (!new_envp)
		return ;
	i = 0;
	while (shell->env_var[i])
		free(shell->env_var[i++]);
	free(shell->env_var);
	shell->env_var = new_envp;
}

int	search_env(t_shell *shell, char *var)
{
	int		i;
	size_t	len;

	len = 0;
	i = 0;
	if (!var)
		return (0);
	while (var[len])
	{							//as not caps are allowed, I'll change this condition. f: what "not caps" mean? only lowercase or only uppercase?
		if (var[len] == '\'' || (var[len] < 65 || var[len] > 90))
			break ;
		len++;
	}
	shell->var_len = len;
	while (shell->env_var[i])
	{
		if (ft_strncmp(shell->env_var[i], var, len) == 0
			&& shell->env_var[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env(t_shell *shell, char *var, char *name)
{
	int	pos;

	pos = search_env(shell, name);
	if (pos >= 0)
	{
		free(shell->env_var[pos]);
		shell->env_var[pos] = ft_strdup(var);
	}
}
