#include "../headers/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n\033[35mMSL> \033[0m", 1);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("\n\033[35mMSL> \033[0m", 1);
}

void	printcommands(t_data *data) // debugging function
{
	t_command *cmd = data->commands;
	int i = 0;

	printf("\n#COMMANDS\n");
	while (cmd)
	{
		printf("cmd:");
		printf("%s\n", cmd->cmds);

		i = 0;
		while (cmd->args[i])
		{
			printf("Arg %d\n", i);
			printf("%s\n", cmd->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
	printf("*****************************\n\n");
}

// Function to check if the quotes are balanced
int	are_quotes_balanced(const char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && double_quote % 2 == 0)
			single_quote++;
		else if (*input == '\"' && single_quote % 2 == 0)
			double_quote++;
		input++;
	}
	return (single_quote % 2 == 0 && double_quote % 2 == 0);
}

// Function to handle input and ensure quotes are closed
char *get_full_input(void)
{
	char *input;
	char *full_input = NULL;
	char *temp;
	int unbalanced_quotes;

	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL) // Handle Ctrl+D
		{
			if (full_input)
				free(full_input);
			printf("Minishell Terminated (ctrl+d)\n");
			return (NULL);
		}

		if (full_input == NULL)
			full_input = ft_strdup(input);
		else
		{
			temp = full_input;
			full_input = ft_strjoin(full_input, input);
			free(temp);
		}
		free(input);

		unbalanced_quotes = !are_quotes_balanced(full_input);
		if (!unbalanced_quotes)
			break;

		write(1, "> ", 2);
	}
	return (full_input);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;


	if (argc > 1)
		exit(0);
	(void)argv;
	data = init_minishell(env);
	signal(SIGINT, handle_sigint);   // handle ctrl+c
	signal(SIGQUIT, handle_sigquit); // handle ctrl+\ //
	while (1)
	{
		write(1, "\033[35mMSL> \033[0m", 14);
		input = get_full_input();
		//input = get_next_line(1);
		if (input == NULL) // ctrl + d
		{
			printf("Minishell Terminated (ctrl+d)\n");
			free_minishell(data);
			return (0);
		}
		printf("\n**********Debugging**********\n");
		printf("#Input received: %s\n", input);
		data->toklist->tokens = ft_tokenize(data->toklist, input);
		free(input);
		if (data->toklist->tokens != NULL)
		{
			int i = 0;
			t_token_list *token;
			token = data->toklist;
			printf("#TOKENS\n");
			while (token->tokens[i])
			{
				printf("%s\n", token->tokens[i]);
				i++;
			}
			printf("\n#toklist tokens count: %d\n", data->toklist->token_count);
			if (data->commands) // reset command struct
			{
				write(1, "reset\n", 6);
				free_command(data->commands);
				data->commands = malloc(sizeof(t_command));
				init_commands(data);
			}
			if (synt_errors_check(data->toklist) == 0)
			{
				ft_sort_tokens(data);
				printcommands(data);
				execute_command(data);
			}

		}
	}
	return (0);
}
