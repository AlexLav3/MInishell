/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:35:57 by fnagy             #+#    #+#             */
/*   Updated: 2024/10/03 13:22:39 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_string;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub_string = malloc(sizeof(char) * (len + 1));
	if (!sub_string)
		return (NULL);
	ft_strlcpy(sub_string, s + start, len + 1);
	return (sub_string);
}
/*
if (start > ft_strlen(s))
	{
		sub_string = malloc(1 * sizeof(char));
		if (!sub_string)
			return (NULL);
		sub_string[0] = '\0';
		return (sub_string);
	}*/
// #include <stdio.h>
// int main (void)
// {
// 	char *s = "Hello World this is me.";
// 	size_t	len = 205;
// 	int	index = 6; //we start indexing at 0!

// 	char *sub = ft_substr(s, index, len);
// 	printf("%s\n", sub);
// }