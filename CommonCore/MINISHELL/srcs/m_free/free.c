#include "../../headers/minishell.h"

void	clear_command_history(t_history **history)
{
	t_history	*current;
	t_history	*next;

	current = *history;
	while (current)
	{
		next = current->next;
		free(current->command);
		free(current);
		current = next;
	}
	*history = NULL;
	rl_clear_history();
}

void	free_minishell(t_data *data)
{
	if (data->toklist)
		free_token_list(data->toklist);
	if (data->commands)
		free_command(data->commands);
	if (data->env)
		free_env_list(data->env);
	if (data->history)
		clear_command_history(&(data->history));
	free(data);
}
