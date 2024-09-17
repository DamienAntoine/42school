#include "../headers/minishell.h"

void ignore_sigquit()
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        perror("Failed to ignore SIGQUIT");
}


void setup_terminal()
{
    struct termios tio;
    if (tcgetattr(STDIN_FILENO, &tio) != 0)
	{
        perror("Failed to get terminal attributes");
        return;
    }

    tio.c_lflag &= ~ECHOCTL; // Disable control characters echoing

    if (tcsetattr(STDIN_FILENO, TCSANOW, &tio) != 0)
        perror("Failed to set terminal attributes");
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n\033[35mMSL> \033[0m", 1);
}

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
	data->toklist->tokens = ft_tokenize(data->toklist, input);
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
	setup_terminal();
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

