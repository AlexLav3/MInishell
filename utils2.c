/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:28:06 by fnagy             #+#    #+#             */
/*   Updated: 2025/05/30 12:40:06 by fnagy            ###   ########.fr       */
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
