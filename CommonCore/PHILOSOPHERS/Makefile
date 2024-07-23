NAME = philo
CFLAGS = -g -Wextra -Wall -Werror
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS = 	./srcs/00_main.c \
		./srcs/01_init.c \
		./srcs/02_handle_threads.c \
		./srcs/03_philo_actions.c \
		./srcs/04_eat.c \
		./srcs/05_monitoring.c \
		./srcs/clear_data.c \
		./srcs/utils.c
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

# Colors
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
	@echo "$(YELLOW)Compiling Philo Project $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Philo Project Compiled Successfully $(DEF_COLOR)"

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
