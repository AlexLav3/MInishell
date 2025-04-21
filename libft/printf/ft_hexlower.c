/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:30:50 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/27 16:57:57 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexlower(int n, const char *format)
{
	char			*symbols;
	unsigned int	value;
	unsigned int	nn;

	value = 0;
	symbols = "0123456789abcdef";
	nn = (unsigned int)n;
	if (nn >= 16)
	{
		value += ft_hexlower(nn / 16, format);
	}
	value += write(1, &symbols[nn % 16], 1);
	return (value);
}
