#include "../../headers/minishell.h"

int	execute_cmd(t_data *data, char **envp, char **full_args)
{
	int		exit_code;
	char	*command_path;

	exit_code = handle_builtin_cmd(data, envp, full_args);
	if (exit_code != -1)
		return (exit_code);
	command_path = get_command_path(data, data->commands->cmds);
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

int	handle_heredocs_before_fork(t_command *cmdtable)
{
	t_redirection	*redir;
	int				pipefd[2];

	while (cmdtable)
	{
		redir = cmdtable->redirects;
		while (redir)
		{
			if (redir->type == 3)
			{
				if (pipe(pipefd) == -1
					|| process_heredoc_lines(redir->file, pipefd[1]) == -1)
				{
					close(pipefd[0]);
					close(pipefd[1]);
					return (-1);
				}
				close(pipefd[1]);
				redir->heredoc_fd = pipefd[0];
			}
			redir = redir->next;
		}
		cmdtable = cmdtable->next;
	}
	return (0);
}

int	execute_command(t_data *data)
{
	t_command	*cmdtable;
	int			num_commands;
	int			exit_code;

	cmdtable = data->commands;
	num_commands = ft_cmdsize(cmdtable);
	exit_code = 0;
	if (handle_heredocs_before_fork(cmdtable) == -1)
		return (1);
	if (cmdtable->next || cmdtable->redirects)
		exit_code = handle_pipes(data, cmdtable, num_commands);
	else
	{
		exit_code = send_command(data);
		if (exit_code != 0)
			return (exit_code);
	}
	return (exit_code);
}
