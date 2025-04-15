/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:33:56 by ferenc            #+#    #+#             */
/*   Updated: 2025/03/03 16:13:33 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

static void	ft_copy_num_to_buffer(char *buffer, int *index, int num)
{
	char	*num_str;
	int		i;

	num_str = ft_itoa(num);
	if (!num_str)
		return ;
	i = 0;
	while (num_str[i] != '\0')
	{
		buffer[*index] = num_str[i];
		(*index)++;
		i++;
	}
	free(num_str);
}

int	my_sprintf(char *buffer, const char *format, ...)
{
	va_list		args;
	int			index;
	const char	*ptr;

	va_start(args, format);
	index = 0;
	ptr = format;
	while (*ptr != '\0')
	{
		if (*ptr == '%' && *(ptr + 1) == 'd')
		{
			ptr++;
			ft_copy_num_to_buffer(buffer, &index, va_arg(args, int));
		}
		else if (*ptr == '%')
			buffer[index++] = *ptr;
		else
			buffer[index++] = *ptr;
		ptr++;
	}
	buffer[index] = '\0';
	va_end(args);
	return (index);
}
/*
What sprintf Does:
	The sprintf function is used to format and
		store a series of characters (including variables) into a string.
	It works like printf, but instead of printing the result to the console,
		it stores the formatted string in a provided character array (buffer).

Syntax:
	buffer:
		A pointer to the character array
		where the formatted string will be stored.
	format:
		A format string that specifies how the output should be formatted.
		It can include placeholders (like %d, %s, etc.)
		for values you want to insert.
	...:
		The values you want to insert into the formatted string
		(passed as arguments).

Return Value:
	It returns the number of characters written to the buffer
	(excluding the null terminator).

Explanation of the Example:
	sprintf(buffer, "Number: %d, Text: %s", number, text);
		formats the string by replacing %d with the value of number (42) and
		 %s with the value of text ("Hello, world!").
	The formatted result is stored in buffer.
	The program then prints the content of buffer and
	the number of characters written to it.

*/
