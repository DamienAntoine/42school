SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
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
	@$(CC) $(FLAGS) srcs/server_bonus.c -L./includes -lftprintf -o $(SERVER_BONUS)
	@$(CC) $(FLAGS) srcs/client_bonus.c -L./includes -lftprintf -o $(CLIENT_BONUS)
	@echo "$(GREEN)Mandatory files ready.$(DEF_COLOR)"

mandatory:
	@echo "$(YELLOW)Preparing mandatory files...$(DEF_COLOR)"
	@$(CC) $(FLAGS) srcs/server.c -L./includes -lftprintf -o $(SERVER)
	@$(CC) $(FLAGS) srcs/client.c -L./includes -lftprintf -o $(CLIENT)
	@echo "$(GREEN)Mandatory files ready.$(DEF_COLOR)"

bonus:
	@echo "$(YELLOW)Preparing bonus files...$(DEF_COLOR)"
	@$(CC) $(FLAGS) srcs/server_bonus.c -L./includes -lftprintf -o $(SERVER_BONUS)
	@$(CC) $(FLAGS) srcs/client_bonus.c -L./includes -lftprintf -o $(CLIENT_BONUS)
	@echo "$(GREEN)Bonus files ready.$(DEF_COLOR)"

clean:
	@echo "$(YELLOW)Cleaning files...$(DEF_COLOR)"
	@rm -rf $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	@echo "$(GREEN)Files cleaned.$(DEF_COLOR)"

fclean: clean
	@rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all
