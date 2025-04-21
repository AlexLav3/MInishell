/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:00:34 by elavrich          #+#    #+#             */
/*   Updated: 2024/10/03 17:37:01 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (ft_c(format) == 'd' || ft_c(format) == 'i' || ft_c(format) == 'u')
			count += ft_chosenbr(va_arg(args, int), format++);
		else if (ft_c(format) == 's')
			count += ft_putstr(va_arg(args, char *), format++);
		else if (ft_c(format) == 'p')
			count += ft_vptr((unsigned long)va_arg(args, void *), format++);
		else if (ft_c(format) == '%')
			count += ft_putchar((char) '%', format++);
		else if (ft_c(format) == 'c')
			count += ft_putchar((char)va_arg(args, int), format++);
		else if (ft_c(format) == 'x' || ft_c(format) == 'X')
			count += ft_chosehex(va_arg(args, int), format++);
		else
			count += ft_putchar_onear(*format);
		format++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	int	a;
// 	int	*ptr;

// 	a = 4;
// 	ptr = &a;
// 	ft_printf(" %u ", a);
// 	ft_printf(" %u\n ", a);

// 	ft_printf(" %d ", a);
// 	printf(" %d\n ", a);

// 	ft_printf(" %i ", a);
// 	printf(" %i\n ", a);

// 	ft_printf(" %x", 455);
// 	printf(" %x\n ", 455);

// 	ft_printf(" %X ", 455);
// 	printf(" %X\n ", 455);

// 	ft_printf(" %p ", ptr);
// 	printf(" %p\n ", ptr);

// 	ft_printf(" %c ", 'a');
// 	printf(" %c\n ", 'a');

// 	ft_printf(" %s ", "string");
// 	printf(" %s\n ", "string");

// 	ft_printf(" %% ");
// 	printf(" %%\n ");

// 	ft_printf("abc65d ");
// 	printf("abc65d\n ");

// 	ft_printf("%d\n", ft_printf("%s\n", NULL));
// }
