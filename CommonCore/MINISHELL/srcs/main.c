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
	write(1, "\nMSL$> ", 8);

}

int	ft_token_counter(t_token_list *toklist)
{
	int	i;

	i = 0;
	while (toklist->tokens[i])
		i++;
	return (i);
}

void	printcommands(t_command *commands) // debugging function
{
	t_command *cmd = commands;
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



int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_data			*data;
	t_command		*commands;
	int				i;

	if (argc > 1)
		exit(0);
	(void)argv;
	data = init_minishell(env);
	signal(SIGINT, handle_sigint); // handle ctrl+c
	while (1)
	{
		write(1, "MSL$> ", 6);
		input = get_next_line(STDIN_FILENO); // alias for '1' in unistd.h


		printf("\n**********Debugging*******************\n");
		printf("#Input received: %s\n", input);

		if (input == NULL)                   // ctrl + d
		{
			printf("Minishell Terminated (ctrl+d)\n");
			exit(0);
		}
		data->toklist->tokens = ft_tokenize(data->toklist, input);	// splits inputs and stores tokens in the structure (lexer)

		/********DEBUGGING********/
		i = 0;
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
				data->commands = ft_sort_tokens(data->toklist, data->commands);	// creates hierarchy and redirects them to corresponding functions (parser to executor)
			commands = data->commands;
			printcommands(commands);
			printf("**************************************\n\n");

			if (ft_strcmp(data->commands->cmds, "pwd") == 0)
				ft_pwd(data->env);
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
