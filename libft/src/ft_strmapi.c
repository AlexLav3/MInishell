/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:04:17 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/21 18:10:33 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "ft_strlen.c"
// #include <ctype.h>
// #include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_str;
	size_t			len;

	len = ft_strlen(s);
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = (*f)(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
// char	to_uppercase(unsigned int i, char c)
// {
// 	return (toupper(c));
// }

// int	main(void)
// {
// 	char const	s1[] = "gdfgsdgdg";
// 	char		*result;

// 	result = ft_strmapi(s1, to_uppercase);
// 	printf("%s\n", result);
// }
