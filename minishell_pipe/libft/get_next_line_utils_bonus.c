/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:40:05 by fnagy             #+#    #+#             */
/*   Updated: 2024/12/09 13:45:26 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_str(char *dest, char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s1[j])
		dest[i++] = s1[j++];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
}

char	*ft_strdup2(char *s)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen2(s) + 1);
	if (!new)
		return (NULL);
	while (*s)
		new[i++] = *s++;
	new[i] = '\0';
	return (new);
}

size_t	ft_strlen2(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != 0)
		++count;
	return (count);
}

char	*ft_substr2(const char *s, unsigned int start, size_t len)
{
	char	*sub_string;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen2(s))
		return (ft_strdup2(""));
	if (ft_strlen2(s + start) < len)
		len = ft_strlen2(s + start);
	sub_string = malloc(sizeof(char) * (len + 1));
	if (!sub_string)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_string[i] = s[start + i];
		i++;
	}
	sub_string[i] = 0;
	return (sub_string);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen2(s1) + ft_strlen2(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_str(str, s1, s2);
	return (str);
}
