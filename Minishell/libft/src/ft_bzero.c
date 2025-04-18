/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:59:52 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/17 21:30:59 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*char_ptr;

	i = 0;
	char_ptr = (char *)s;
	while (i < n)
	{
		char_ptr[i] = 0;
		i++;
	}
}

// int	main(void)
// {
// 	char	str[90] = "erkgherkghfd0ukgauh";
// 	char	str2[90] = "erkgherkghfd0ukgauh";

// 	bzero(str, 20);
// 	ft_bzero(str2, 20);
// 	printf("%s, %s", str, str2);
// }
