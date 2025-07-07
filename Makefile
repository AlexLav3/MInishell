NAME = minishell
BIN = bin
CC = cc -g -Wall -Werror -Wextra -Wunused-function
CFLAGS =  -Ilibft 
LDFLAGS = -lreadline

SOURCES = main.c init.c input.c utils.c exect.c process_cmd.c\
		envp_handle.c clean_exit.c sig.c builtin.c\
		pipe/pipe_handle_001.c pipe/pipe_handle_002.c pipe/pipe_prepare.c\
		counters.c tokens.c path.c make_args.c \
		process_w.c var_utils.c\
		redirections/executor_main.c redirections/executor_utils.c redirections/heredoc.c\
		redirections/parser_redir.c redirections/parser_redir_utils.c redirections/pipeline.c\
		redirections/redir_apply.c redirections/token_utils.c\
		syntax_error.c\
				

OBJECTS = $(SOURCES:%.c=$(BIN)/%.o)

LIB_FT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB_FT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB_FT) $(LDFLAGS)

$(BIN)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(BIN)

fclean: clean
	rm -f $(NAME)

re: fclean all