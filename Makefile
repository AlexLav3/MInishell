NAME = minishell
BIN = bin
CC = cc -g
CFLAGS =  -Ilibft 
LDFLAGS = -lreadline

SOURCES = main.c init.c input.c utils.c exect.c process_cmd.c\
		envp_handle.c clean_exit.c sig.c builtin.c\
		pipe/pipe_handle_001.c pipe/pipe_handle_002.c pipe/pipe_prepare.c\
		redirections/redir_utils.c	redirections/pipe_redir.c redirections/exc_pipes.c \
		redirections/redir.c redirections/parse_handle.c counters.c tokens.c path.c make_args.c \
		process_w.c


# OBJECTS = $(SOURCES:.c=.o)
OBJECTS = $(SOURCES:%.c=$(BIN)/%.o)

LIB_FT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB_FT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB_FT) $(LDFLAGS)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@
$(BIN)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(BIN)

fclean: clean
	rm -f $(NAME)

re: fclean all