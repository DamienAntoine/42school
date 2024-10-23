#include "../../headers/minishell.h"

// int	check_redirection_before_fork(t_data *data)
// {
// 	t_command		*cmdtable;
// 	int				fd;
// 	t_redirection	*redir;

// 	cmdtable = data->commands;
// 	while (cmdtable)
// 	{
// 		redir = cmdtable->redirects;
// 		while (redir)
// 		{
// 			fd = open_redirection(redir);
// 			if (fd == -1)
// 			{
// 				perror(redir->file);
// 				return (-1);
// 			}
// 			if (redir->type != 3)
// 				close(fd);
// 			redir = redir->next;
// 		}
// 		cmdtable = cmdtable->next;
// 	}
// 	return (0);
// }

int	send_command(t_data *data)
{
	char		**envp;
	t_command	*cmdtable;
	int			arg_count;
	char		**full_args;
	int			exit_code;
	char		*command_path;

	envp = env_list_to_array(data->env);
	cmdtable = data->commands;
	full_args = prepare_full_args(cmdtable, &arg_count);
	exit_code = 0;
	if (data == NULL)
	{
		fprintf(stderr, "Error: Data pointer is NULL.\n");
		return (1);
	}
	data->error_occurred = 0;
	if (!cmdtable || !cmdtable->cmds)
	{
		free_split(envp);
		data->state.last_exit_status = 0;
		return (0);
	}
	if (is_builtin(cmdtable->cmds))
		exit_code = execute_builtin_command(cmdtable, data);
	else
	{
		command_path = get_command_path(cmdtable->cmds);
		if (!command_path)
		{
			exit_code = handle_exec_error(data, cmdtable->cmds);
			free_split(envp);
			free(full_args);
			set_exit_status(exit_code, data);
			return (exit_code);
		}
		exit_code = execute_external_command(cmdtable, full_args, envp, data);
		if (exit_code == 126 || exit_code == 127)
			exit_code = handle_exec_error(data, command_path);
		free(command_path);
	}
	free_split(envp);
	free(full_args);
	set_exit_status(exit_code, data);
	return (exit_code);
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
