#include "../../headers/minishell.h"

t_data	*init_minishell(char **env)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->commands = malloc(sizeof(t_command));
	if (!data->commands)
	{
		perror("Failed to allocate memory for commands");
		free(data);
		return (NULL);
	}
	data->toklist = malloc(sizeof(t_token_list));
//	printf("Allocated toklist: %p\n", data->toklist);
	if (!data->toklist) {
		perror("Failed to allocate memory for toklist");
		free(data->commands);
		free(data);
		return (NULL);
	}
	data->env = NULL;
	data->redirects = NULL;
	init_env(env, &data->env);
	if (!data->env)
	{
		fprintf(stderr, "Failed to initialize environment variables\n");
		free(data->toklist);
		free(data->commands);
		free(data);
		return (NULL);
	}
	init_commands(data);
	data->toklist->tokens = NULL;
	data->state.last_exit_status = 0;
	return (data);
}

void	init_commands(t_data *data)
{
	data->commands->args = NULL;
	data->commands->cmds = NULL;
	data->commands->next = NULL;
}
