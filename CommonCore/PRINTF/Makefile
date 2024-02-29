CC = cc
CFLAGS = -Wall -Wextra -Werror -I../includes
NAME = libftprintf.a
SRCS = srcs/ft_printchar.c srcs/ft_printf.c srcs/ft_printnbr.c srcs/ft_printstr.c srcs/ft_printunsigned.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_MAKE = $(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) libft
	ar rc $(NAME) $(OBJS) $(LIBFT)

clean:
	rm -rf $(OBJ_DIR)
	$(LIBFT_MAKE) clean

fclean: clean
	rm -rf $(NAME)
	$(LIBFT_MAKE) fclean

re: fclean all

.PHONY: all clean fclean re libft

libft:
	$(LIBFT_MAKE)
