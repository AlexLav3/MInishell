/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:09:16 by fnagy             #+#    #+#             */
/*   Updated: 2024/10/03 12:16:23 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*j;
	size_t			i;

	i = 0;
	j = (unsigned char *)s;
	while (i < n)
	{
		j[i] = c;
		i++;
	}
	return (s);
}
// #include <stdio.h>
// int main (void)
// {
//     char string[7] = "Hello!";
//     printf("old: %s\n", string);
//     ft_memset(string, 65, 20);
//     printf("new: %s\n", string);
// }