#include "../../headers/minishell.h"

t_data	*init_minishell(char **env)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	printf("Allocated data: %p\n", data);
	if (!data)
		return (NULL);

	data->commands = malloc(sizeof(t_command));
	printf("Allocated commands: %p\n", data->commands);
	data->toklist = malloc(sizeof(t_token_list));
	printf("Allocated toklist: %p\n", data->toklist);
	data->env = NULL;
	//data->env = malloc(sizeof(t_env));
	//printf("Allocated env: %p\n", data->env);
	//data->redirects = malloc(sizeof(t_redirection));

	init_env(env, &data->env);
	if (!data->commands || !data->toklist || !data->env)
	{
		free(data->commands);
		free(data->toklist);
		free(data->env); //no need to free because it's null now.
		free(data);
		printf("Freed data and all sub-elements due to failure\n");
		return (NULL);
	}

	init_commands(data);
	data->toklist->tokens = NULL;
	data->state.last_exit_status = 0;
	return (data);
}

void    init_commands(t_data *data)
{
	data->commands->args = NULL;
	data->commands->cmds = NULL;
	data->commands->next = NULL;
}
