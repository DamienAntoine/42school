#include "../../headers/minishell.h"

t_data	*init_minishell(char **env)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->commands = malloc(sizeof(t_command));
	data->toklist = malloc(sizeof(t_token_list));
	data->env = malloc(sizeof(t_env));
	//data->redirects = malloc(sizeof(t_redirection));
	if (!data->commands || !data->toklist || !data->env/* || !data->redirects*/)
	{
		free(data->commands);
		free(data->toklist);
		free(data->env);
		//free(data->redirects);
		free(data);
		return (NULL);
	}
	init_env(env, &data->env);
	init_commands(data);
	//init_redirections(data);
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
