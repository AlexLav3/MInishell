NAME = libft.a
CFLAGS = -g
SOURCES = src/ft_atoi.c src/ft_bzero.c src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c \
src/ft_isprint.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c  src/ft_memmove.c src/ft_memset.c src/ft_strchr.c \
src/ft_strlcpy.c src/ft_strlen.c src/ft_strncmp.c src/ft_strnstr.c src/ft_strrchr.c src/ft_tolower.c src/ft_toupper.c \
src/ft_split.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c src/ft_substr.c \
src/ft_calloc.c src/ft_strjoin.c src/ft_strtrim.c src/ft_strmapi.c src/ft_itoa.c src/ft_striteri.c src/ft_strdup.c src/ft_strlcat.c \
get_next_line/get_next_line_utils.c get_next_line/get_next_line.c \
printf/ft_atoi.c printf/ft_c.c printf/ft_chosehex.c printf/ft_hexlower.c printf/ft_hexupper.c printf/ft_pointer.c printf/ft_printf.c printf/ft_putchar_onear.c printf/ft_putchar.c printf/ft_putnbr.c\
printf/ft_putnewl.c printf/ft_putstr.c printf/ft_putunsint.c printf/ft_chosenbr.c\
src/ft_strcmp.c

BONUS_SOURCES = src/ft_lstadd_back.c src/ft_lstadd_front.c src/ft_lstclear.c src/ft_lstdelone.c src/ft_lstiter.c \
src/ft_lstlast.c src/ft_lstmap.c src/ft_lstnew.c src/ft_lstsize.c

OBJECTS = $(SOURCES:.c=.o)
BONUS_OBJS	= $(BONUS_SOURCES:.c=.o)

all:${NAME} ${OBJECTS}

${NAME} : ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(BONUS_OBJS)

fclean: clean
	rm -f ${NAME}

bonus:$(OBJECTS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJECTS) $(BONUS_OBJS)

re: fclean all
