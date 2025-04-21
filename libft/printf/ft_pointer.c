/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:37:47 by elavrich          #+#    #+#             */
/*   Updated: 2024/10/01 20:20:51 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long	ft_ptr(unsigned long num)
{
	char			*symbols;
	unsigned long	value;

	value = 0;
	symbols = "0123456789abcdef";
	if (num >= 16)
	{
		value += ft_ptr(num / 16);
	}
	value += write(1, &symbols[num % 16], 1);
	return (value);
}

unsigned long	ft_vptr(unsigned long num, const char *format)
{
	unsigned long	value;
	char			*symbols;

	(void)format;
	symbols = "0123456789abcdef";
	value = 0;
	if (!num)
		value += write(1, "(nil)", 5);
	else
	{
		value += write(1, "0x", 2);
		value += ft_ptr(num);
	}
	return (value);
}
