/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:23:37 by elavrich          #+#    #+#             */
/*   Updated: 2024/10/01 20:21:41 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int				ft_atoi(const char *nptr);
int				ft_printf(const char *format, ...);
int				ft_chosehex(int n, const char *format);
int				ft_hexlower(int n, const char *format);
int				ft_hexupper(int n, const char *format);
unsigned long	ft_vptr(unsigned long num, const char *format);
int				ft_putchar_onear(char c);
char			ft_c(const char *format);
int				ft_putchar(char c, const char *format);
int				ft_putstr(char *s, const char *format);
int				ft_putnbr(int n, const char *format);
void			ft_newl(void);
int				ft_putunsint(unsigned int n, const char *format);
int				ft_chosenbr(int n, const char *format);

#endif
