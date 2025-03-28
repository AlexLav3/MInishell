/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:00:35 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/18 18:33:25 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*char_ptr;
	unsigned char	c_ptr;

	i = 0;
	char_ptr = (unsigned char *)s;
	c_ptr = (unsigned char)c;
	while (i < n)
	{
		if (char_ptr[i] == c_ptr)
			return ((void *)&char_ptr[i]);
		i++;
	}
	if (i == n)
		return (NULL);
	return (0);
}
// int	main(void)
// {
// 	char	str[90] = "hkjdfhgjkh";
// 	char	str2[90] = "hkjdfhgjkh";

// 	ft_memchr(str, 200, 10);
// 	memchr(str2, 200, 10);
// 	printf("%s\n", str);
// 	printf("%s", str2);
// }
