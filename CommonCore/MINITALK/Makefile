SERVER = server
CLIENT = client
PRINTF = ./includes
CC = gcc
FLAGS = -Wall -Wextra -Werror

 DEF_COLOR = \033[0;39m
 GRAY = \033[0;90m
 RED = \033[0;91m
 GREEN = \033[0;92m
 YELLOW = \033[0;93m
 BLUE = \033[0;94m
 MAGENTA = \033[0;95m
 CYAN = \033[0;96m
 WHITE = \033[0;97m

all:
	@echo "$(YELLOW)Preparing mandatory files...$(DEF_COLOR)"
	@$(CC) $(FLAGS) srcs/server.c -L./includes -lftprintf -o $(SERVER)
	@$(CC) $(FLAGS) srcs/client.c -L./includes -lftprintf -o $(CLIENT)
	@echo "$(GREEN)Mandatory files ready.$(DEF_COLOR)"

mandatory:
	@echo "$(YELLOW)Preparing mandatory files...$(DEF_COLOR)"
	@$(CC) $(FLAGS) srcs/server.c -L./includes -lftprintf -o $(SERVER)
	@$(CC) $(FLAGS) srcs/client.c -L./includes -lftprintf -o $(CLIENT)
	@echo "$(GREEN)Mandatory files ready.$(DEF_COLOR)"

clean:
	@echo "$(YELLOW)Cleaning files...$(DEF_COLOR)"
	@rm -rf $(SERVER) $(CLIENT)
	@echo "$(GREEN)Files cleaned.$(DEF_COLOR)"

fclean: clean
	@rm -f $(SERVER) $(CLIENT)

re: fclean all
