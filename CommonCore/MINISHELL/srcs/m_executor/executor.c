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

void	handle_exec_error(t_data *data, char *exec_target)
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
					exit(126);
				}
				else
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": command not found\n", STDERR_FILENO);
					data->error_occurred = 1;
					exit(127);
				}
			}
			// if regular file but no permission (not currently working as intended ?)
			if (S_ISREG(path_stat.st_mode) && access(exec_target, X_OK) == -1)
			{
				if (errno == EACCES)
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
					data->error_occurred = 1;
					exit(126);
				}
			}
			// if its a file but not executable
			ft_putstr_fd(exec_target, STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			data->error_occurred = 1;
			exit(127);
		}
		else
		{
			// if stat fails (check if file exists)
			if (errno == ENOENT)
			{
				if (exec_target[0] == '.' || exec_target[0] == '/')
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				}
				else
				{
					ft_putstr_fd(exec_target, STDERR_FILENO);
					ft_putstr_fd(": command not found\n", STDERR_FILENO);
				}
				data->error_occurred = 1;
				exit(127);
			}
		}
		// default error
		ft_putstr_fd(exec_target, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->error_occurred = 1;
		exit(127);
	}
}

char **prepare_full_args(t_command *cmdtable, int *arg_count)
{
	int i;
	char **full_args;

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
    return full_args;
}

int execute_builtin_command(t_command *cmdtable, t_data *data)
{
    if (cmdtable->redirects != NULL)
    {
        if (setup_redirection(cmdtable->redirects) == -1)
        {
            printf("Error setting up redirections\n");
            return 1; // Handle error
        }
    }

    // Directly execute built-in command without forking
    return execute_builtin(cmdtable, data);
}


int execute_external_command(t_command *cmdtable, char **full_args, char **envp, t_data *data)
{
    pid_t pid = fork();
	char *cmd_path;
    char *exec_target;
	int exit_code;
	int status;

	cmd_path = get_command_path(cmdtable->cmds);
	if (cmd_path)
		exec_target = cmd_path;
	else
		exec_target = cmdtable->cmds;

    if (pid == 0) // Child
    {
        if (cmdtable->redirects != NULL)
        {
            if (setup_redirection(cmdtable->redirects) == -1)
                exit(1);
        }
        if (execve(exec_target, full_args, envp) == -1)
            handle_exec_error(data, exec_target);
    }
    else if (pid > 0) // Parent
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
        return 1;
    }
	return (0);
}

int check_redirection_before_fork(t_data *data)
{
    t_command *cmdtable = data->commands;
    int fd;

    while (cmdtable) // Iterate through each command in the command list
    {
        t_redirection *redir = cmdtable->redirects;
        while (redir) // Iterate through the redirections for this command
        {
            fd = open_redirection(redir);
            if (fd == -1)
            {
                perror(redir->file); // Provide feedback on which redirection failed
                return -1; // Indicate failure
            }
            if (redir->type != 3) // If not a here-document
                close(fd); // Close file descriptor
            redir = redir->next; // Move to the next redirection
        }
        cmdtable = cmdtable->next; // Move to the next command
    }
    return 0; // Indicate success
}

int send_command(t_data *data)
{
    char **envp = env_list_to_array(data->env);
    t_command *cmdtable = data->commands;
    int arg_count;
    char **full_args = prepare_full_args(cmdtable, &arg_count);
    int exit_code = 0;

	if (data == NULL)
	{
		fprintf(stderr, "Error: Data pointer is NULL.\n");
		return 1;
	}

    if (data->error_occurred)
        return 1;

    if (!cmdtable || !cmdtable->cmds)
    {
        free_split(envp);
        data->state.last_exit_status = 0;
        return 0;
    }

    // Check for built-ins
    if (is_builtin(cmdtable->cmds))
        exit_code = execute_builtin_command(cmdtable, data);
    else
    {
        // Get the full command path
        char *command_path = get_command_path(cmdtable->cmds);
        if (!command_path)
        {
            handle_exec_error(data, cmdtable->cmds);
            free_split(envp);
            free(full_args);
            return 127; // Command not found
        }
        exit_code = execute_external_command(cmdtable, full_args, envp, data);
        if (exit_code == 126 || exit_code == 127) // Permission denied or command not found
            handle_exec_error(data, command_path);
        free(command_path);
    }

    free_split(envp);
    free(full_args);
    set_exit_status(exit_code, data); // This should properly set last_exit_status
    return exit_code; // Return the exit code
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
    t_command *cmdtable = data->commands;
    int num_commands = ft_cmdsize(cmdtable);
    int exit_code = 0;
	int check;

	if (cmdtable->redirects == NULL && !cmdtable->next)
    {
	    exit_code = send_command(data);
        if (exit_code != 0)
            return exit_code; // If a built-in command fails, return the error code
    }

    // Step 1: Handle Redirections
    if (cmdtable->redirects != NULL)
	{
        check = check_redirection_before_fork(data);
        if (check == -1)
            exit_code = 1; // Indicate failure
    }

    // Step 2: Handle Pipes
	if (cmdtable->next || cmdtable->redirects)
    	exit_code = handle_pipes(data, cmdtable, num_commands);
    if (exit_code == -1)
        return -1;
    return (exit_code);
}
