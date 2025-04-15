/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:28:13 by fnagy             #+#    #+#             */
/*   Updated: 2024/10/13 19:42:19 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_formats(va_list argp, const char element)
{
	int	counter;

	counter = 0;
	if (element == 'c')
		counter += ft_print_chr(va_arg(argp, int));
	else if (element == 's')
		counter += ft_print_str(va_arg(argp, char *));
	else if (element == 'd' || element == 'i')
		counter += ft_print_nbr(va_arg(argp, int));
	else if (element == '%')
		counter += ft_print_chr('%');
	else if (element == 'p')
		counter += ft_print_ptr(va_arg(argp, void *));
	else if (element == 'x' || element == 'X')
		counter += ft_print_hex(va_arg(argp, unsigned int), (element == 'X'));
	else if (element == 'u')
		counter += ft_print_dec((unsigned long)va_arg(argp, unsigned int));
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	argp;
	int		counter;
	size_t	i;

	counter = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(argp, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			counter += (ft_formats(argp, format[i + 1]));
			i++;
		}
		else
			counter += ft_print_chr(format[i]);
		i++;
	}
	va_end(argp);
	return (counter);
}
