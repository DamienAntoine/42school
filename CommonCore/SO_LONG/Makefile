NAME = so_long
CFLAGS = -Wextra -Wall
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS = $(SRCS_DIR)/so_long.c
GETNEXTLINE := includes/get_next_line/*.c
OBJS = $(OBJS_DIR)/$(notdir $(SRCS:.c=.o))
MLX_LIB = mlx/
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(MLX_LIB) $(OBJS_DIR) $(NAME)

$(MLX_LIB):
	@if [ ! -d "mlx" ]; then \
	echo "$(YELLOW)cloning mlx $(DEF_COLOR)"; \
	git clone https://github.com/42Paris/minilibx-linux.git mlx; \
	fi
	@echo "$(GREEN)mlx cloned $(DEF_COLOR)"
	@echo "$(YELLOW)making mlx.a $(DEF_COLOR)"
	@make -C $(MLX_LIB)
	@echo "$(GREEN)mlx.a created $(DEF_COLOR)"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling so_long $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(GETNEXTLINE) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)so_long Compiled $(DEF_COLOR)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	@if [ -d "mlx" ]; then \
	make clean -C mlx/; \
	rm -rf mlx/; \
	fi
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
