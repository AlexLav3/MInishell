NAME = minishell
CC = cc -g
CFLAGS =  -Ilibft 
LDFLAGS = -lreadline

SOURCES = main.c init.c input.c utils.c exect.c process_cmd.c\
		envp_handle.c clean_exit.c sig.c builtin.c\
		pipe/pipe_handle_001.c pipe/pipe_handle_002.c pipe/pipe_prepare.c\
		split_tokens/split_tokens.c\

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