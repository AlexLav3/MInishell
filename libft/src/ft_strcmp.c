/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:56:53 by fnagy             #+#    #+#             */
/*   Updated: 2025/04/07 17:52:25 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* return -1 for NULl not part of original strcmp,
but I guess we better have it for future projects to hand NULL inputs.*/
// if (!s1 || !s2)
// 	return (-1);
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// #include <stdio.h>
// int main (void)
// {
// 	char *s1 = "";
// 	char *s2 = "Hello Wor";
// 	int i = ft_strcmp(s1, s2);
// 	printf("%i\n", i);
// }