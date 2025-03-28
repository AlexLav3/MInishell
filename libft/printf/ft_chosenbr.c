/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chosenbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:23:26 by elavrich          #+#    #+#             */
/*   Updated: 2024/10/01 20:22:04 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_chosenbr(int n, const char *format)
{
	int	count;

	count = 0;
	if (ft_c(format) == 'u')
		count += ft_putunsint(n, format);
	else
		count += ft_putnbr(n, format);
	return (count);
}
