NAME = push_swap
CFLAGS = -Wextra -Wall -Werror
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS = ./srcs/calculate_costs.c \
		./srcs/clear_stacks.c \
		./srcs/find_bf.c \
		./srcs/find_mean.c \
		./srcs/inputs_checks.c \
		./srcs/main.c \
		./srcs/push_swap.c \
		./srcs/push.c \
		./srcs/reverse_rotate.c \
		./srcs/rotate.c \
		./srcs/print_operations.c \
		./srcs/sort_stacks.c \
		./srcs/swap.c
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling $< to $@
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling Push_Swap $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) ./includes/libftprintf.a -o $(NAME)
	@echo "$(GREEN)Push_Swap Compiled $(DEF_COLOR)"

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re