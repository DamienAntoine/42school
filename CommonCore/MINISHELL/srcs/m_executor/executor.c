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

int	handle_builtin_command(t_data *data, int *exit_code)
{
	if (is_builtin(data->commands->cmds))
	{
		*exit_code = execute_builtin_command(data->commands, data);
		return (1);
	}
	return (0);
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

int	execute_cmd(t_data *data, char **envp, char **full_args)
{
	int		exit_code;
	char	*command_path;

	exit_code = handle_builtin_cmd(data, envp, full_args);
	if (exit_code != -1)
		return (exit_code);
	command_path = get_command_path(data->commands->cmds);
	if (!command_path)
	{
		exit_code = handle_exec_error(data, data->commands->cmds);
		free_split(envp);
		free(full_args);
		set_exit_status(exit_code, data);
		return (exit_code);
	}
	exit_code = execute_external_command(data->commands, full_args, envp, data);
	if (exit_code == 126 || exit_code == 127)
		exit_code = handle_exec_error(data, command_path);
	free(command_path);
	free_split(envp);
	free(full_args);
	set_exit_status(exit_code, data);
	return (exit_code);
}

int	send_command(t_data *data)
{
	char	**envp;
	char	**full_args;
	int		result;

	result = prepare_command(data, &envp, &full_args);
	if (result != -1)
		return (result);
	return (execute_cmd(data, envp, full_args));
}

int	ft_cmdsize(t_command *lst)
{
	size_t	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int	execute_command(t_data *data)
{
	t_command	*cmdtable;
	int			num_commands;
	int			exit_code;
	int			check;

	cmdtable = data->commands;
	num_commands = ft_cmdsize(cmdtable);
	exit_code = 0;
	if (cmdtable->redirects == NULL && !cmdtable->next)
	{
		exit_code = send_command(data);
		if (exit_code != 0)
			return (exit_code);
	}
	if (cmdtable->redirects != NULL)
	{
		check = check_redirection_before_fork(data);
		if (check == -1)
			exit_code = 1;
	}
	if (cmdtable->next || cmdtable->redirects)
		exit_code = handle_pipes(data, cmdtable, num_commands);
	if (exit_code == -1)
		return (-1);
	return (exit_code);
}
