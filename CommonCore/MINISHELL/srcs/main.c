#include "../headers/minishell.h"

void	printcommands(t_data *data) // debugging function
{
	t_command		*cmd;
	t_token_list	*token;
	int				i;

	cmd = data->commands;
	token = data->toklist;


	printf("\n**********Debugging**********\n");
	printf("#TOKENS\n");

	i = 0;
	while (token->tokens[i])
	{
		printf("%s\n", token->tokens[i]);
		i++;
	}
	printf("\n\n#COMMANDS\n");
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
	printf("\n*****************************\n\n");
}

void	reset_toklist(t_data *data)
{
	if (data->toklist->tokens)
	{
		free_split(data->toklist->tokens);
		data->toklist->tokens = NULL;
		data->toklist->token_count = 0;
	}
}

int	handle_input(t_data *data)
{
	char	*input;


	input = get_full_input();
	if (!input)
	{
		//printf("\nMinishell Terminated (ctrl+d)\n");
		free_minishell(data);
		return (0);
	}
	data->toklist->tokens = ft_tokenize(data, input);
	free(input);
	return (1);
}

void	reset_command(t_data *data)
{
	free_command(data->commands);
	data->commands = malloc(sizeof(t_command));
	init_commands(data);
}

void reset_redirection(t_data *data)
{
    t_redirection *current = data->redirects;
    t_redirection *next;

    // Traverse the linked list and free each redirection
    while (current != NULL)
    {
        next = current->next; // Save the next node
        free(current->file);  // Free the file name if dynamically allocated
        free(current);        // Free the current node
        current = next;       // Move to the next node
    }

    // Reset the head pointer to NULL after freeing the list
    data->redirects = NULL;
}



int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argv;
	if (argc > 1)
		exit(0);
	data = init_minishell(env);
	//setup_terminal();
	signal(SIGINT, handle_sigint);
	ignore_sigquit();
	while (1)
	{
		reset_toklist(data);
		if (!handle_input(data))
			return (0);
		reset_command(data);
		reset_redirection(data);
		if (!has_synt_errors(data->toklist))
		{
			ft_sort_tokens(data);
			//printcommands(data);//delete when everything is finished
			execute_command(data);
		}
	}
	return (free_minishell(data), 0);
}

