/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:28:06 by fnagy             #+#    #+#             */
/*   Updated: 2025/05/30 13:31:06 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// place here the extra functions after norminette
void	set_var(char **cmd, t_shell *shell, char *equal, int i)
{
	char	*var;
	char	*name;

	var = ft_strdup(cmd[i]);
	if (!var)
		return ;
	*equal = '\0';
	name = cmd[i];
	if (search_env(shell, name) < 0)
		add_env(shell, var);
	else
		update_env(shell, var, name);
	free(var);
	*equal = '=';
}

int	copy_env_vars(char **dest, char **src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			while (i-- > 0)
				free(dest[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
