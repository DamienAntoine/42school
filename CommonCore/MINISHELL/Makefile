CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

LDFLAGS = -lreadline

# main and builtins
SRCS =  ./includes/gnl.c ./srcs/main.c ./srcs/builtins/cd.c ./srcs/builtins/echo.c ./srcs/builtins/env.c ./srcs/builtins/exit.c\
		./srcs/builtins/export.c ./srcs/builtins/pwd.c ./srcs/builtins/unset.c ./srcs/builtins/etc.c\

# m_init
SRCS += ./srcs/m_init/init.c ./srcs/m_init/init_env.c\

# m_executor
SRCS += ./srcs/m_executor/executor.c ./srcs/m_executor/pipes.c ./srcs/m_executor/redirection.c\

# m_free
SRCS += ./srcs/m_free/free.c\

# m_lexer
SRCS += ./srcs/m_lexer/synt_checks.c ./srcs/m_lexer/tokenize.c\

# m_parser
SRCS += ./srcs/m_parser/sort_tokens.c ./srcs/m_parser/input.c\

# utils
SRCS += ./srcs/utils/utils_str.c ./srcs/utils/utils_error.c ./srcs/utils/utils_print.c ./srcs/utils/utils_checker.c\
		./srcs/utils/terminal_signal.c ./srcs/utils/command_path.c ./srcs/utils/util_exe.c ./srcs/utils/util_pipe.c\
		./srcs/utils/util_redir.c ./srcs/utils/util_token.c



OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(LDFLAGS)

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

