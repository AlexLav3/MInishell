
NAME = pipex
BIN = bin

SRC  =	src/pipex_003.c\


OBJS	= $(SRC:src/%c=$(BIN)/%o)

LIB_FT = libft/
LIB_FT_A = $(LIB_FT)libft.a

INCLUDES = -I/usr/include

UNAME := $(shell uname)
RM	= rm -rf

CFLAGS = -Wall -Werror -Wextra -O3 -g -I${LIB_FT}
LFLAGS = libft/libft.a
#LFLAGS = -L$(LIB_FT) -lft

ifeq ($(UNAME), Darwin) # iMac / iOS
	CC = gcc
	LFLAGS += -framework OpenGL -framework AppKit
else ifeq ($(UNAME), FreeBSD) # FreeBSD./
	CC = clang
else #Linux and others...
	CC = cc
	LFLAGS += -lbsd -lXext -lX11 -lm
endif


all: $(NAME)

#$(NAME): $(BIN) $(OBJS) $(LIB_FT_A)
#	${CC} $(OBJS) $(LFLAGS) -o $(NAME) 
$(NAME): $(BIN) $(OBJS) $(LIB_FT_A)
	${CC} $(OBJS) $(CFLAGS) $(LFLAGS) -o $(NAME)

$(BIN)/%o: src/%c
	${CC} -c $< $(CFLAGS) $(IFLAGS) -o $@

$(BIN):
	mkdir -p $(BIN)  $(BIN)/commands

$(LIB_FT_A):
	make -C $(LIB_FT)

clean:
	make clean -C $(LIB_FT)
	$(RM) $(BIN)

fclean: clean
	make fclean -C $(LIB_FT)
	$(RM) $(NAME)

re: fclean $(NAME)

norm:
	norminette src/ include/ libft/

# to call: make valgrind ARGS="4 5 6 7 2 3 9 4" or ARGS='"4 5 6 7 2 3 9 4"'
valgrind: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJ		: $(OBJ)\n"

.PHONY: all clean fclean re show