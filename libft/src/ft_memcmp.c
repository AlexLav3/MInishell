/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:00:45 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/18 18:42:20 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*char_ptr;
	const char	*char_ptr2;

	i = 0;
	char_ptr = (const char *)s1;
	char_ptr2 = (const char *)s2;
	while (i < n)
	{
		if ((unsigned char)char_ptr[i] != (unsigned char)char_ptr2[i])
			return ((unsigned char)char_ptr[i] - (unsigned char)char_ptr2[i]);
		i++;
	}
	return (0);
}
// int	main(void)
// {
// 	char	str1[50] = "dsfsdfgdff";
// 	char	str2[50] = "ds";

// 	printf("%i\n %i", ft_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
// }
