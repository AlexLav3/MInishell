/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:23:43 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/25 00:24:00 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*process_word(char *word, t_shell *shell, int flag)
{
	char	*exp;

	if (flag != EXPAND || !word)
		return (word);
	if (ft_strchr(word, '$') != NULL)
	{
		exp = handle_dollar(word, shell);
		if (!exp)
			return (free(word), ft_strdup(""));
	}
	else
		return (word);
	free(word);
	return (exp);
}
