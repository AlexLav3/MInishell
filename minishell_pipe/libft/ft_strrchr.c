/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:33 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 12:50:05 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_len;

	s_len = ft_strlen(s);
	while (s_len >= 0)
	{
		if (s[s_len] == (char) c)
			return ((char *)(s + s_len));
		s_len--;
	}
	return (NULL);
}
// #include <stdio.h>
// int main (void)
// {
// 	int c = '\0';
// 	char *s = "Hello";
// 	char* result;
// 	result = ft_strrchr(s, c);
// 	printf("%s\n", result);
// }