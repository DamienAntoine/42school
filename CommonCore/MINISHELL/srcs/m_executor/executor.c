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


int	send_command(t_data *data)
{
	char		**envp = env_list_to_array(data->env);
	char		*cmd_path;
	char		**full_args;
	t_command	*cmdtable = data->commands;
	pid_t		pid;
	int			status;
	int			arg_count;
	int			exit_code;
	int			i;

	arg_count = 0;
	while (cmdtable->args[arg_count] != NULL)
		arg_count++;
	full_args = malloc((arg_count + 2) * sizeof(char *));
	if (!full_args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	full_args[0] = cmdtable->cmds;
	i = 0;
	while (i < arg_count)
	{
		full_args[i + 1] = cmdtable->args[i];
		i++;
	}
	// NULL terminate the array
	full_args[arg_count + 1] = NULL;
	if (!cmdtable || !cmdtable->cmds)
	{
		free_split(envp);
		data->state.last_exit_status = 0;
		free(full_args);
		return (0);
	}

	// Handle built-ins directly in the context of the pipe
	if (is_builtin(cmdtable->cmds))
	{
		if (data->redirects == NULL) // no redirections
			exit_code = execute_builtin(cmdtable, data); // execute directly
		else // if redirections
		{
			setup_redirection(data->redirects);
			exit_code = execute_builtin(cmdtable, data);
		}
		free_split(envp);
		free(full_args);
		return (exit_code);
	}


	// fork external commands
	pid = fork();
	if (pid == 0) // child process
	{
		setup_redirection(data->redirects);
		cmd_path = get_command_path(cmdtable->cmds);

		// if cmd_path, use cmd_path instead of cmdtable->cmds
		char *exec_target;
		if (cmd_path)
			exec_target = cmd_path;
		else
			exec_target = cmdtable->cmds;

		// check if file exists
		int fd = open(exec_target, O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES) // Check for permission denied error
			{
				ft_putstr_fd(exec_target, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				exit(126); // Permission denied
			}
			else if (exec_target[0] == '.' || exec_target[0] == '/')// if file doesnt exist and input is a path
			{
				ft_putstr_fd(exec_target, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				exit(127); // File doesn't exist
			}
			else
			{
				// if not a path, cmd not found
				ft_putstr_fd(exec_target, STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
				exit(127);
			}
		}
		else
		{
			// check if is directory
			char buffer[1];
			if (read(fd, buffer, 1) == -1)
			{
				// if read returns -1, means its a dir
				if (errno == EISDIR) // if open is used on a directory, it returns EISDIR into errno
				{
					// only print "Is a directory" for paths
					if (exec_target[0] == '.' || exec_target[0] == '/')
					{
						ft_putstr_fd(exec_target, STDERR_FILENO);
						ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
						close(fd);
						exit(126);
					}
					else
					{
						// if not a path, cmd not found
						ft_putstr_fd(exec_target, STDERR_FILENO);
						ft_putstr_fd(": command not found\n", STDERR_FILENO);
						close(fd);
						exit(127); // Command not found
					}
				}
			}
			close(fd);
		}
		// try executing
		if (execve(exec_target, full_args, envp) == -1)
		{
			if (errno == ENOENT)// if execve failed because file or dir dont exist, returns ENOENT
			{
				ft_putstr_fd(exec_target, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				exit(127);
			}
			else
			{
				// everything else is cmd not found
				ft_putstr_fd(exec_target, STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
				exit(127);
			}
		}
	}
	else if (pid > 0) // parent
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			set_exit_status(exit_code, data);
			free_split(envp);
			free(full_args);
			return (exit_code);
		}
		else if (WIFSIGNALED(status))
		{
			exit_code = 128 + WTERMSIG(status);
			set_exit_status(exit_code, data);
			free_split(envp);
			free(full_args);
			return (exit_code);
		}
	}
	else
	{
		perror("fork");
		data->state.last_exit_status = 1;
		free_split(envp);
		free(full_args);
		return (1);
	}
	free_split(envp);
	free(full_args);
	return (1);
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

int execute_command(t_data *data)
{
	t_command	*cmdtable;
	int			num_commands;

	num_commands = ft_cmdsize(data->commands);
	cmdtable = data->commands;

	if (cmdtable->next != NULL) // means there's a pipe
	{
		handle_pipe(data, num_commands);
		return (0);
	}
	// no pipe, just check command syntax and execute
	send_command(data);
	return (data->state.last_exit_status);
}

