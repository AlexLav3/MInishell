/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:42:09 by fnagy             #+#    #+#             */
/*   Updated: 2024/12/27 13:38:31 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
*/

static size_t	word_counts(char const *str, char c)
{
	int		i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			wc++;
		i++;
	}
	return (wc);
}

static size_t	word_len(char const *str, char c, size_t i)
{
	size_t	j;

	j = 0;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

static void	*free_all(char **array, size_t w_position)
{
	size_t	i;

	i = 0;
	while (i < w_position)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	w_position;
	size_t	i;
	size_t	w_len;

	i = 0;
	w_position = 0;
	array = (char **)malloc(sizeof(char *) * (word_counts(s, c) + 1));
	if (!array)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			w_len = word_len(s, c, i);
			array[w_position] = ft_substr(s, i, w_len);
			if (!array[w_position++])
				return (free_all(array, w_position - 1));
			i = i + w_len;
		}
		else
			i++;
	}
	array[w_position] = 0;
	return (array);
}

/*
ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", 94:'^'):
*/

/*#include <stdio.h>

int	main()
{
	char	*s = "^^^1^^2a,^^^^3^^^^--h^^^^";
	char	**v = ft_split(s, '^');
	while (*v)
		printf("%s\n", *v++);
}
*/