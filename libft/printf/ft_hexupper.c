/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:34:38 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/27 16:58:56 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexupper(int n, const char *format)
{
	char			*symbols;
	int				value;
	unsigned int	nn;

	nn = (unsigned int)n;
	value = 0;
	symbols = "0123456789ABCDEF";
	if (nn >= 16)
	{
		value += ft_hexupper(nn / 16, format);
	}
	value += write(1, &symbols[nn % 16], 1);
	return (value);
}
