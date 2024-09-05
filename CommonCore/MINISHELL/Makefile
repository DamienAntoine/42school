CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

# main and builtins
SRCS =  ./includes/gnl.c ./srcs/main.c ./srcs/builtins/cd.c ./srcs/builtins/echo.c ./srcs/builtins/env.c ./srcs/builtins/exit.c\
		./srcs/builtins/export.c ./srcs/builtins/pwd.c ./srcs/builtins/unset.c\

# m_init
SRCS += ./srcs/m_init/init.c ./srcs/m_init/init_env.c\

# m_executor
SRCS += ./srcs/m_executor/executor.c ./srcs/m_executor/pipes.c ./srcs/m_executor/redirection.c\

# m_free
SRCS += ./srcs/m_free/free.c\

# m_lexer
SRCS += ./srcs/m_lexer/synt_checks.c ./srcs/m_lexer/tokenize.c\

# m_parser
SRCS += ./srcs/m_parser/create_redirects.c ./srcs/m_parser/sort_tokens.c\

# utils
SRCS += ./srcs/utils/utils_str.c ./srcs/utils/utils_error.c ./srcs/utils/utils_print.c



OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

