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



void	printcommands(char *input, t_data *data) // debugging function
{
	t_command		*cmd;
	t_token_list	*token;
	int				i;

	cmd = data->commands;
	token = data->toklist;

	printf("\n**********Debugging**********\n");
	printf("#Input received: %s\n", input);
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
	printf("*****************************\n\n");
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;


	if (argc > 1)
		exit(0);
	(void)argv;
	data = init_minishell(env);
	setup_terminal();
	signal(SIGINT, handle_sigint);   // handle ctrl+c
	ignore_sigquit();
	while (1)
	{
		write(1, "\033[35mMSL> \033[0m", 14);
		data->redirects = NULL;
		input = get_full_input();
		if (input == NULL) // ctrl + d
		{
			printf("\nMinishell Terminated (ctrl+d)\n");
			free_minishell(data);
			return (0);
		}
		data->toklist->tokens = ft_tokenize(data->toklist, input);
		if (data->toklist->tokens != NULL)
		{
			if (data->commands) // reset command struct
			{
				write(1, "reset\n", 6);
				free_command(data->commands);
				data->commands = malloc(sizeof(t_command));
				init_commands(data);
			}
			if (has_synt_errors(data->toklist) == 0)
			{
				ft_sort_tokens(data);
				printcommands(input, data);
				free(input);
				execute_command(data);
			}
		}
	}
	return (0);
}
