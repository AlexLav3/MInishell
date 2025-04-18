/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:01:03 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/21 15:32:37 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_strlen.c"
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// void	to_upper(unsigned int i, char *s)
// {
// 	if (*s >= 'a' && *s <= 'z')
// 	{
// 		*s = *s - 32;
// 	}
// }

// int	main(void)
// {
// 	char	s1[] = "gdfgsdgdg";

// 	ft_striteri(s1, to_upper);
// 	printf("%s\n", s1);
// }
