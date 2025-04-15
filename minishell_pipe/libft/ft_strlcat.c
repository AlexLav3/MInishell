/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:22:43 by fnagy             #+#    #+#             */
/*   Updated: 2024/10/03 16:37:28 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			dst_size;
	size_t			src_size;

	i = 0;
	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dst_size >= size || size == 0)
		return (src_size + size);
	while (src[i] != '\0' && i < (size - dst_size - 1))
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (src_size + dst_size);
}
// #include <stdio.h>
// int main (void)
// {
//     char *src = " World";
//     char dst[20]= "Hello";
//     size_t length= ft_strlcat(dst, src, 8);
//     printf("my l: %zu, dst: %s\n", length, dst);

// }