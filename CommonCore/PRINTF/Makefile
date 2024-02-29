CC = cc
CFLAGS = -Wall -Wextra -Werror -I../includes
PRINTF = printf.a
SRCS = srcs/ft_printchar.c srcs/ft_printptr.c srcs/ft_printf.c srcs/ft_printnbr.c srcs/ft_printstr.c srcs/ft_printunsigned.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_MAKE = $(MAKE) -C $(LIBFT_DIR)

$(shell mkdir -p $(OBJ_DIR))

$(OBJ_DIR)/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(PRINTF)

$(PRINTF): $(OBJS) libft
	ar rc $(PRINTF) $(OBJS) $(LIBFT)

clean:
	rm -rf $(OBJS)
	$(LIBFT_MAKE) clean

fclean: clean
	rm -rf $(PRINTF)
	$(LIBFT_MAKE) fclean

re: fclean all

.PHONY: all clean fclean re libft

libft:
	$(LIBFT_MAKE)
