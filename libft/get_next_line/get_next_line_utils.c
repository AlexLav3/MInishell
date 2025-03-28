/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:39:29 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/05 18:08:37 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_g(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_g(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*concat;

	concat = malloc(ft_strlen_g(s1) + ft_strlen_g(s2) + 1);
	if (!concat)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		concat[i] = s1[i];
	j = -1;
	while (s2[++j])
		concat[i + j] = s2[j];
	concat[i + j] = '\0';
	free(s1);
	return (concat);
}

int	ft_strchr_g(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
