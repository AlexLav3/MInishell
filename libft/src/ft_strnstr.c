/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:00:54 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/18 19:39:10 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	k = 0;
	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		k = 0;
		while (big[i + k] == little[k] && i + k < len)
		{
			k++;
			if (little[k] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
// int	main(void)
// {
// 	const char	big[90] = "gdgfkdag";
// 	const char	little[90] = "a";
// 	size_t		len;

// 	len = 9;
// 	printf("%s\n", ft_strnstr(big, little, len));
// }
