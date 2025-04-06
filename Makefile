NAME = minishell
CC = cc -g
CFLAGS =  -lreadline -I${LIB_FT}
LDFLAGS = -lreadline

SOURCES = main.c init.c input.c utils.c exect.c envp_handle.c get_path.c
OBJECTS = $(SOURCES:.c=.o)

LIB_FT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB_FT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB_FT) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all