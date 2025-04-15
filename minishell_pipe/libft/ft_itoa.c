/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:31:49 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/07 09:27:28 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
*/
static int	get_len(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = n * -1;
	}
	if (n == 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*allocation(int len)
{
	char	*tmp;

	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[0] = '0';
	return (tmp);
}

char	*ft_itoa(int n)
{
	char			*new_str;
	long			new_n;
	size_t			i;
	size_t			len;

	new_n = n;
	len = get_len(new_n);
	new_str = allocation(len);
	if (!new_str)
		return (NULL);
	if (n < 0)
		new_n = new_n * -1;
	i = len - 1;
	while (new_n != 0)
	{
		new_str[i] = (new_n % 10) + 48;
		new_n = new_n / 10;
		i--;
	}
	if (n < 0)
		new_str[0] = '-';
	new_str[len] = '\0';
	return (new_str);
}
// #include <stdio.h>
// int main (void)
// {
// 	int x1 = -2147483648;
// 	char *string1 = ft_itoa(x1);
// 	printf("%s\n", string1);
// 	int x2 = 2147483647;
// 	char *string2 = ft_itoa(x2);
// 	printf("%s\n", string2);
// 	int x3 = 0;
// 	char *string3 = ft_itoa(x3);
// 	printf("%s\n", string3);
// 	int x4 = -123;
// 	char *string4 = ft_itoa(x4);
// 	printf("%s\n", string4);
// 	free(string1);
// 	free(string2);
// 	free(string3);
// 	free(string4);
// }