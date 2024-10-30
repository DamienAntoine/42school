#include "../../headers/minishell.h"

int	handle_null_data(t_data *data)
{
	if (data == NULL)
	{
		fprintf(stderr, "Error: Data pointer is NULL.\n");
		return (1);
	}
	return (0);
}

int	handle_null_commands(t_data *data, char **envp)
{
	if (!data->commands || !data->commands->cmds)
	{
		free_split(envp);
		data->state.last_exit_status = 0;
		return (0);
	}
	return (-1);
}

int	prepare_command(t_data *data, char ***envp, char ***full_args)
{
	int	arg_count;

	*envp = env_list_to_array(data->env);
	*full_args = prepare_full_args(data->commands, &arg_count);
	if (handle_null_data(data))
		return (1);
	data->error_occurred = 0;
	if (handle_null_commands(data, *envp) == 0)
		return (0);
	return (-1);
}

int	handle_builtin_cmd(t_data *data, char **envp, char **full_args)
{
	int	exit_code;

	if (is_builtin(data->commands->cmds))
	{
		exit_code = execute_builtin_command(data->commands, data);
		free_split(envp);
		free(full_args);
		set_exit_status(exit_code, data);
		return (exit_code);
	}
	return (-1);
}
