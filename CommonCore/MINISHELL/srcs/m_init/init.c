#include "../../headers/minishell.h"

t_data	*init_minishell(char **env)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	printf("Allocated data: %p\n", (void*)data);
	if (!data)
		return (NULL);


	data->commands = malloc(sizeof(t_command));
	if (!data->commands)
	{
		perror("Failed to allocate memory for commands");
		free(data);
		return NULL;
	}
	printf("Allocated commands: %p\n", data->commands);
	printf("Allocated commands: %p\n", (void*)data->commands);

	data->toklist = malloc(sizeof(t_token_list));
	printf("Allocated toklist: %p\n", data->toklist);
	if (!data->toklist) {
        perror("Failed to allocate memory for toklist");
        free(data->commands);
        free(data);
        return NULL;
    }
	data->env = NULL;
	data->redirects = NULL;
	//data->env = malloc(sizeof(t_env));
	//printf("Allocated env: %p\n", data->env);
	//data->redirects = malloc(sizeof(t_redirection));
/*

	if (!data->commands || !data->toklist || !data->env)
	printf("Allocated toklist: %p\n", (void*)data->toklist);

	data->env = malloc(sizeof(t_env));
	printf("Allocated env: %p\n", (void*)data->env);

	data->redirects = malloc(sizeof(t_redirection));
	printf("Allocated redirects: %p\n", (void*)data->redirects);

	if (!data->commands || !data->toklist || !data->env || !data->redirects)
	{
		free(data->commands);
		free(data->toklist);
		free(data->env); //no need to free because it's null now.
		free(data);
		printf("Freed data and all sub-elements due to failure\n");
		return (NULL);
	}
	*/
	init_env(env, &data->env);
	    if (!data->env) { // Ensure env was initialized
        fprintf(stderr, "Failed to initialize environment variables\n");
        free(data->toklist);
        free(data->commands);
        free(data);
        return NULL;
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
