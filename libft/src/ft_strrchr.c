/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:00:29 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/17 21:11:28 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*char_ptr;

	char_ptr = (char *)s;
	i = 0;
	while (char_ptr[i])
		i++;
	while (i >= 0)
	{
		if (char_ptr[i] == (char)c)
			return (&char_ptr[i]);
		i--;
	}
	if (c == '\0')
		return (&char_ptr[i]);
	return (NULL);
}
