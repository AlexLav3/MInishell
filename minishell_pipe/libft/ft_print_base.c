/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:08:41 by fnagy             #+#    #+#             */
/*   Updated: 2024/10/13 19:35:56 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// count lenght for hex and dec functions which have different base
int	ft_count_len(unsigned int element, int n)
{
	int	len;

	len = 0;
	while (element != 0)
	{
		len++;
		element = element / n;
	}
	return (len);
}

// hex fucntion to print x or X hex and also used for pointer
void	ft_hex(unsigned long hex, unsigned int capital)
{
	char	*base;

	base = "0123456789abcdef";
	if (hex < (unsigned long)16)
	{
		if (capital && base[hex] >= 97 && base[hex] <= 102)
			ft_putchar_fd(base[hex] - 32, 1);
		else
			ft_putchar_fd(base[hex], 1);
	}
	if (hex >= (unsigned long)16)
	{
		ft_print_hex(hex / 16, capital);
		ft_print_hex(hex % 16, capital);
	}
}

int	ft_print_hex(unsigned long hex, unsigned int capital)
{
	if (hex == 0)
		return (write(1, "0", 1));
	else
		ft_hex(hex, capital);
	return (ft_count_len(hex, 16));
}

// dec functions to print element U (unsigned)
void	ft_dec(unsigned long dec)
{
	char	*base;

	base = "0123456789";
	if (dec < (unsigned long)10)
		ft_putchar_fd(base[dec], 1);
	if (dec >= (unsigned long)10)
	{
		ft_dec(dec / 10);
		ft_dec(dec % 10);
	}
}

int	ft_print_dec(unsigned long dec)
{
	if (dec == 0)
		return (write(1, "0", 1));
	else
		ft_dec(dec);
	return (ft_count_len(dec, 10));
}
