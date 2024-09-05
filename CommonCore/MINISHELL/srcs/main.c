#include "../headers/minishell.h"

void	handle_sigint(int sig)
{
/*
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
*/
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
}

// Function to check if the quotes are balanced
int are_quotes_balanced(const char *input)
{
    int single_quote = 0;
    int double_quote = 0;

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
	int	unbalanced_quotes = 0;

    while (1)
    {
        input = get_next_line(STDIN_FILENO); // Read the input

        if (input == NULL) // Handle Ctrl+D
        {
            printf("Minishell Terminated (ctrl+d)\n");
            free(full_input);
            exit(0);
        }

        // Concatenate the input to full_input
        if (full_input == NULL)
            full_input = ft_strdup(input);
        else
        {
            temp = full_input;
            full_input = ft_strjoin(full_input, input);
            free(temp);
        }

        free(input); // Free the current line input
		unbalanced_quotes = !are_quotes_balanced(full_input);
		if (!unbalanced_quotes)
			break ;
/*
        // Check if quotes are balanced
        if (!are_quotes_balanced(full_input))
			unbalanced_quotes = 1;
        else
		{
			if (unbalanced_quotes)
				unbalanced_quotes = 0;
			else
				break ;
		}
*/
        // If quotes are not balanced, prompt for more input
        write(1, "> ", 2);
    }

    return full_input;
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_data			*data;
	//t_command		*commands;


	if (argc > 1)
		exit(0);
	(void)argv;
	data = init_minishell(env);


	signal(SIGINT, handle_sigint); // handle ctrl+c
	signal(SIGQUIT, handle_sigquit); //handle ctrl+\ //

	while (1)
	{
		write(1, "\033[35mMSL> \033[0m", 14);
		input = get_full_input();


		printf("\n**********Debugging**********\n");
		printf("#Input received: %s\n", input);

		if (input == NULL)                   // ctrl + d
		{
			printf("Minishell Terminated (ctrl+d)\n");
			free_minishell(data);
			exit(0);
		}
		data->toklist->tokens = ft_tokenize(data->toklist, input);	// splits inputs and stores tokens in the structure (lexer)
		if (data->toklist->tokens != NULL)
		{
			/********DEBUGGING********/
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
			//printf("\n#commands structure initialized: %p\n", (void *)data->commands);

				if (data->commands) // reset command struct
				{
					free_command(data->commands);
					data->commands = malloc(sizeof(t_command));
					init_commands(data);
				}
				if (synt_errors_check(data->toklist) == 0)							// checks tokens syntax and prints syntax errors
					ft_sort_tokens(data);	// creates hierarchy and redirects them to corresponding functions (parser to executor)
			
				printcommands(data);
				printf("*****************************\n\n");


				execute_command(data);
				/*
				if (ft_strcmp(data->commands->cmds, "env") == 0) // replace this with executor
					ft_env(data->env);*/
		}
		// start exec with checking commands and arguments
		// executor works with fork() and execve(), handles redirections (>, <, >>, <<) and pipes (|), and also handles error management(command not found, ...)
		// example of how lexer->parser->executor thing works: https://imgur.com/a/PTod73J

		free(input);
		free(data->toklist->tokens);
		data->toklist->tokens = NULL;
		// data->toklist->token_count = 0;
	}
	return (0);
}
