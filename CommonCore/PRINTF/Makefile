CC = cc
CFLAGS = -Wall -Wextra -Werror -I../includes
NAME = libftprintf.a
SRCS = srcs/ft_printchar.c srcs/ft_printf.c srcs/ft_printnbr.c srcs/ft_printstr.c srcs/ft_printunsigned.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
LIBFT_DIR = libft
$(OBJ_DIR)/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

libft: @$(MAKE) -C $(LIBFT_DIR)