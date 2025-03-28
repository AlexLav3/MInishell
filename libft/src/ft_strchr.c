/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:00:20 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/21 21:05:01 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*char_ptr;

	i = 0;
	char_ptr = (char *)s;
	while (char_ptr[i])
	{
		if (char_ptr[i] == (unsigned char)c)
		{
			return (&char_ptr[i]);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
		return (&char_ptr[i]);
	return (NULL);
}
// int	main(void)
// {
// 	const char	s[] = "teste";
// 	char ch = 'e';
// 	printf("%s",ft_strchr(s,ch));
// }
