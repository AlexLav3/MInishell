/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:40:26 by fnagy             #+#    #+#             */
/*   Updated: 2024/10/03 13:29:25 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	all_size;

	all_size = nmemb * size;
	if (nmemb && size != (all_size / nmemb))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}
/*
safe malloc - heap overflow
*/
// #include <stdio.h>
// int main(void)
// {
// 	char * s;
// 	s = (char *)ft_calloc(1, 0);
// 	if (!s)
// 	{
// 		printf("fail\n");
// 		return (1);
// 	}
// 	int i;
// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf("%c\n", s[i]);
// 		i++;
// 	}
// }