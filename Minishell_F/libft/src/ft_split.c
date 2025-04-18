/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:34:42 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/04 18:23:41 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char c, const char charset)
{
	return (c == charset);
}

static int	count_segments(const char *str, char charset)
{
	int	count;
	int	in_segment;

	count = 0;
	in_segment = 0;
	while (*str)
	{
		if (is_separator(*str, charset))
		{
			if (in_segment)
			{
				in_segment = 0;
			}
		}
		else
		{
			if (!in_segment)
			{
				count++;
				in_segment = 1;
			}
		}
		str++;
	}
	return (count);
}

static char	*copy_segment(const char *s, int start, int end)
{
	char	*segment;
	int		length;
	int		i;

	i = 0;
	length = end - start;
	segment = malloc(length + 1);
	if (!segment)
		return (NULL);
	while (i < length)
	{
		segment[i] = s[start + i];
		i++;
	}
	segment[length] = '\0';
	return (segment);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		k;
	char	**array;
	int		start;

	i = 0;
	k = 0;
	array = malloc((count_segments(s, c) + 1) * sizeof(char *));
	if (!array)
		return (free(array), NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[k] = copy_segment(s, start, i);
			k++;
		}
		else
			i++;
	}
	array[k] = NULL;
	return (array);
}

void	f_free(char **split_argc)
{
	int	i;

	i = 0;
	if (!split_argc)
		return ;
	while (split_argc[i])
	{
		free(split_argc[i]);
		i++;
	}
	free(split_argc);
}
// int	main(void)
// {
// 	char	s1[90] = "split ||this|for|me|||||!|";
// 	char	s2;
// 	char	**result;
// 	int		i;

// 	s2 = '|';
// 	i = 0;
// 	result = ft_split(s1, s2);
// 	while (result[i])
// 	{
// 		printf("%s", result[i]);
// 		i++;
// 	}
// }
