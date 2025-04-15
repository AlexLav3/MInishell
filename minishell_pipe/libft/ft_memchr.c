/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:37 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 12:54:16 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *) s == (unsigned char) c)
			return ((void *) s);
		s++;
	}
	return (NULL);
}
// #include <stdio.h>
// int main (void)
// {
// 	void *r;
// 	char *string = "Hello!";
// 	r = ft_memchr((void*)string, 'i', 5);
// 	printf("result: %s\n", (char *)r);
// }