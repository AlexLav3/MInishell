/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:56:18 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/27 21:37:16 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n, const char *format)
{
	char	num;
	int		i;
	long	nn;

	nn = (long)n;
	i = 0;
	if (nn == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nn < 0)
	{
		write(1, "-", 1);
		nn = -nn;
		i++;
	}
	if (nn >= 10)
	{
		i += ft_putnbr((nn / 10), format);
	}
	num = (nn % 10) + '0';
	write(1, &num, 1);
	i++;
	return (i);
}
// int main()
// {
// 	ft_putnbr_fd(-21474848, -1);
// }
