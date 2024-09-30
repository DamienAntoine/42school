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
	if (input[0] == '\0' || input[0] == '\n')
	{
		free(input);
		return (1);
	}
	data->toklist->tokens = ft_tokenize(data, input);
	free(input);
	return (data->toklist->tokens != NULL); //returns 1 if tokenize worked and 0 if not
}

void	reset_command(t_data *data)
{
	free_command(data->commands);
	data->commands = malloc(sizeof(t_command));
	init_commands(data);
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
		if (!has_synt_errors(data->toklist))
		{
			ft_sort_tokens(data);
			//printcommands(data);//delete when everything is finished
			execute_command(data);

			if (data->redirects)
				free_redirections(data->redirects);
		}
	}
	return (free_minishell(data), 0);
}

