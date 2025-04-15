/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:34:32 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 13:34:06 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char) c)
	{
		if (!*s++)
			return (0);
	}
	return ((char *) s);
}
// #include <stdio.h>
// int main (void)
// {
// 	int c = '\0';
// 	char *s = "Hello";
// 	char* result;
// 	result = ft_strchr(s, c);
// 	printf("%s\n", result);
// }