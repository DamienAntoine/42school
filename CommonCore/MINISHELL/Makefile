CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS = ./srcs/main.c ./srcs/builtins/cd.c ./srcs/builtins/echo.c ./srcs/builtins/env.c ./srcs/builtins/exit.c\
		./srcs/builtins/export.c ./srcs/builtins/pwd.c ./srcs/builtins/unset.c ./srcs/builtins/utils.c\
		./srcs/m_env/env_value.c  ./srcs/m_env/init_env.c\
		./srcs/m_free/free_env.c\
		./srcs/m_lexer/synt_checks.c ./srcs/m_lexer/tokenize.c\
		./srcs/m_parser/create_redirects.c ./srcs/m_parser/sort_tokens.c


OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
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

