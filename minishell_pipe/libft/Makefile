# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/21 12:01:41 by fnagy             #+#    #+#              #
#    Updated: 2025/03/19 12:17:33 by ferenc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c\
		ft_isascii.c	ft_isprint.c	ft_strlen.c\
		ft_toupper.c	ft_tolower.c	ft_strlcpy.c\
		ft_strlcat.c	ft_strncmp.c	ft_atoi.c\
		ft_memset.c	ft_bzero.c	ft_memcpy.c\
		ft_memmove.c	ft_strchr.c	ft_strrchr.c\
		ft_strdup.c	ft_memchr.c	ft_memcmp.c\
		ft_strnstr.c	ft_calloc.c	ft_substr.c\
		ft_strjoin.c	ft_strtrim.c	ft_split.c\
		ft_itoa.c	ft_strmapi.c\
		ft_striteri.c	ft_putchar_fd.c	ft_putstr_fd.c\
		ft_putendl_fd.c	ft_putnbr_fd.c\
		ft_print_base.c	ft_print_ptr.c	ft_print_utils.c\
		ft_printf.c	get_next_line.c	get_next_line_utils.c\
		get_next_line_utils_bonus.c	get_next_line_bonus.c\
		max_of_three.c\
		ft_atol.c\
		linked_list_insert_single.c\
		linked_list_insert_double.c\
		linked_list_deallocate.c\
		linked_list_change.c\
		linked_list_check.c\
		linked_list_finds.c\

		
OFILES = $(SRCS:%.c=%.o)

BSRCS = ft_lstnew.c	ft_lstadd_front.c	ft_lstsize.c\
		ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c\
		ft_lstclear.c	ft_lstiter.c	ft_lstmap.c

BOFILES = $(BSRCS:%.c=%.o)

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

bonus: ${OFILES} ${BOFILES}
	ar rc ${NAME} ${OFILES} ${BOFILES}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES) $(BOFILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)


.PHONY:	all	clean	fclean	re
