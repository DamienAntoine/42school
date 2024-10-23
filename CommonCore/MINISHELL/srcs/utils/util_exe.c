#include "../../headers/minishell.h"

int	execute_builtin(t_command *cmdtable, t_data *data)
{
	if (ft_strcmp(cmdtable->cmds, "cd") == 0)
		return (ft_cd(data));
	else if (ft_strcmp(cmdtable->cmds, "echo") == 0)
		return (ft_echo(data));
	else if (ft_strcmp(cmdtable->cmds, "env") == 0)
		return (ft_env(data->env));
	else if (ft_strcmp(cmdtable->cmds, "pwd") == 0)
		return (ft_pwd(data->env));
	else if (ft_strcmp(cmdtable->cmds, "unset") == 0)
		return (handle_unset(&data->env, data->toklist->tokens));
	else if (ft_strcmp(cmdtable->cmds, "exit") == 0)
		return (ft_exit(data));
	else if (ft_strcmp(cmdtable->cmds, "export") == 0)
		return (handle_export(data));
	return (1);
}

int	handle_exec_error(t_data *data, char *exec_target)
{
	struct stat	path_stat;

	if (data->error_occurred != 1)
	{
		if (stat(exec_target, &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				if (exec_target[0] == '.' || exec_target[0] == '/')
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
					data->error_occurred = 1;
					return (126);
				}
				else
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": command not found\n", STDERR_FILENO);
					data->error_occurred = 1;
					return (127);
				}
			}
			if (access(exec_target, F_OK) == 0
				&& access(exec_target, R_OK) == -1 && access(exec_target, W_OK) == -1
				&& access(exec_target, X_OK) == -1)
			{
				ft_putstr_fd(exec_target, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				data->error_occurred = 1;
				return (126);
			}
			else if (access(exec_target, F_OK) == 0 && access(exec_target,
					X_OK) == -1)
			{
				ft_putstr_fd(exec_target, STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
				data->error_occurred = 1;
				return (127);
			}
			else if (S_ISREG(path_stat.st_mode) && access(exec_target, X_OK)
				== -1)
			{
				if (errno == EACCES)
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
					data->error_occurred = 1;
					return (126);
				}
			}
		}
		else
		{
			if (errno == ENOENT)
			{
				if (exec_target[0] == '.' || exec_target[0] == '/')
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": No such file or directory\n",
						STDERR_FILENO);
				}
				else
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": command not found\n", STDERR_FILENO);
				}
				data->error_occurred = 1;
				return (127);
			}
		}
		ft_putstr_fd(exec_target, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->error_occurred = 1;
		return (127);
	}
	return (0);
}

char	**prepare_full_args(t_command *cmdtable, int *arg_count)
{
	int		i;
	char	**full_args;

	i = 0;
	*arg_count = 0;
	while (cmdtable->args[*arg_count] != NULL)
		(*arg_count)++;
	full_args = malloc((*arg_count + 2) * sizeof(char *));
	if (!full_args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	full_args[0] = cmdtable->cmds;
	while (i < *arg_count)
	{
		full_args[i + 1] = cmdtable->args[i];
		i++;
	}
	full_args[*arg_count + 1] = NULL;
	return (full_args);
}

int	execute_builtin_command(t_command *cmdtable, t_data *data)
{
	if (cmdtable->redirects != NULL)
	{
		if (setup_redirection(cmdtable->redirects) == -1)
		{
			printf("Error setting up redirections\n");
			return (1);
		}
	}
	return (execute_builtin(cmdtable, data));
}

int	execute_external_command(t_command *cmdtable, char **full_args, char **envp,
		t_data *data)
{
	pid_t	pid;
	char	*cmd_path;
	char	*exec_target;
	int		exit_code;
	int		status;

	pid = fork();
	cmd_path = get_command_path(cmdtable->cmds);
	if (cmd_path)
		exec_target = cmd_path;
	else
		exec_target = cmdtable->cmds;
	if (pid == 0)
	{
		if (cmdtable->redirects != NULL)
		{
			if (setup_redirection(cmdtable->redirects) == -1)
				exit(1);
		}
		if (execve(exec_target, full_args, envp) == -1)
			exit(handle_exec_error(data, exec_target));
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else
			exit_code = 128 + WTERMSIG(status);
		return (exit_code);
	}
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}
