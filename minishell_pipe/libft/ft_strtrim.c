/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:12:45 by fnagy             #+#    #+#             */
/*   Updated: 2024/10/03 12:16:23 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && isset(s1[start], set))
		start++;
	len = ft_strlen(s1) - start;
	while (len > 0 && isset((s1 + start)[len - 1], set))
		len--;
	return (ft_substr(s1, start, len));
}
// #include <stdio.h>
// int main (void)
// {
// 	char	*s = "aaaaaaa";
// 	char *set = "a";
// 	char *trim = ft_strtrim(s, set);
// 	printf("%s\n", trim);
// }