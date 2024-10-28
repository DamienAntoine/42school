#include "../../headers/minishell.h"

int	handle_exec_error(t_data *data, char *exec_target)
{
	struct stat	path_stat;

	if (data->error_occurred != 1)
	{
		if (stat(exec_target, &path_stat) == 0)
			return (handle_exec_error_if_part(data, exec_target, path_stat));
		else
			return (handle_exec_error_else_part(data, exec_target));
	}
	return (0);
}

int	handle_parent_process(pid_t pid)
{
	int	status;
	int	exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = 128 + WTERMSIG(status);
	return (exit_code);
}

int	execute_child_process(t_command *cmdtable, char **full_args, char **envp,
		t_data *data)
{
	char	*exec_target;

	exec_target = get_command_path(data, cmdtable->cmds);
	if (!exec_target)
		exec_target = cmdtable->cmds;
	if (cmdtable->redirects != NULL)
	{
		if (setup_redirection(cmdtable->redirects) == -1)
			exit(1);
	}
	if (execve(exec_target, full_args, envp) == -1)
		return (-1);
	return (0);
}

int	execute_external_command(t_command *cmdtable, char **full_args, char **envp,
		t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execute_child_process(cmdtable, full_args, envp, data) == -1)
			return (126);
	}
	else if (pid > 0)
		return (handle_parent_process(pid));
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}
