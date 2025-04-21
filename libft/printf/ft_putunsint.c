/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:17:37 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/27 21:57:11 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsint(unsigned int n, const char *format)
{
	char	num;
	int		i;

	i = 0;
	if (n >= 10)
		i += ft_putnbr(n / 10, format);
	num = (n % 10) + '0';
	write(1, &num, 1);
	i++;
	return (i);
}
