/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:23:43 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/27 22:25:56 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*process_word(char *word, t_shell *shell, int flag)
{
	char	*exp;
	int		len;

	len = 0;
	printf("word: %s\n", word);
	if (flag != EXPAND || !word)
		return (word);
	if (ft_strchr(word, '$') != NULL)
	{
		len = ft_strlen(word);
		if (word[len - 1] == '$')
			return (word);
		exp = handle_dollar(word, shell);
		if (!exp)
			return (word);
	}
	else
		return (word);
	free(word);
	return (exp);
}
