NAME = minishell
SRCS = \
	main.c \
	./execute/execute.c ./execute/execute_builtin.c ./execute/execute_heredoc.c ./execute/execute_search.c ./execute/execute_utils.c ./execute/execute_construct.c \
	./parse/make_tree.c ./parse/make_token.c ./parse/make_token_utils.c ./parse/make_piece.c ./parse/make_piece_utils.c ./parse/make_check.c ./parse/make_utils.c \
	./builtin/builtin_echo.c ./builtin/builtin_cd.c ./builtin/builtin_pwd.c ./builtin/builtin_env.c ./builtin/builtin_exit.c \
	./enviroment_var/env.c ./enviroment_var/env_utils.c \
	./signal/signal.c \
	./error/error.c \
	./utils/utils.c
OBJS = $(SRCS:.c=.o)
LIB_DIR = libft
LIB_NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -I $(LIB_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB_DIR) $(LIB_NAME)
	$(CC) $(CFLAGS) -lreadline -L $(LIB_DIR) -lft -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIB_DIR) $@
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIB_DIR)/$(LIB_NAME)
	$(RM) $(NAME)

re: fclean all
