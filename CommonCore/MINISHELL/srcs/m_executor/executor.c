#include "../../headers/minishell.h"

void	execute_builtin(t_command *cmdtable, t_data *data)
{
	if (ft_strcmp(cmdtable->cmds, "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(cmdtable->cmds, "echo") == 0)
		ft_echo(data);
		//ft_echo(data->toklist, &(data->state), data->env);
	else if (ft_strcmp(cmdtable->cmds, "env") == 0)
		ft_env(data->env);
	else if (ft_strcmp(cmdtable->cmds, "pwd") == 0)
		ft_pwd(data->env);
	else if (ft_strcmp(cmdtable->cmds, "unset") == 0)
		handle_unset(&data->env, data->toklist->tokens);
	else if (ft_strcmp(cmdtable->cmds, "exit") == 0)
	{
		if (data->toklist->token_count == 1)
			ft_exit(data, 0);
		else
			ft_exit(data, ft_atoi(data->toklist->tokens[1]));
	}
	else if (ft_strcmp(cmdtable->cmds, "export") == 0)
	{
		if (data->toklist->token_count == 1)
			print_export(data->env, &(data->state));
		else
			handle_export(&data->env, data->toklist->tokens, &(data->state));
	}
	else if (ft_strcmp(cmdtable->cmds, "cat") == 0)
		ft_cat(data);
	else if (ft_strcmp(cmdtable->cmds, "grep") == 0)
		ft_grep(data);
}

void send_command(t_data *data)
{
    char **envp = env_list_to_array(data->env);
    t_command *cmdtable = data->commands;

    if (!cmdtable || !cmdtable->cmds)
	{
        ft_putstr_fd("No command provided\n", STDERR_FILENO);
        free_split(envp);
        return;
    }

    if (is_builtin(cmdtable->cmds))
	{
		if (data->redirects == NULL)
		    execute_builtin(cmdtable, data); // Execute built-in commands directly
		else
		{
            // Handle built-in commands with redirections by forking
            pid_t pid = fork();
            if (pid == 0)
            {  // Child process
                printf("Built-in command with redirection.\n");
                setup_redirection(data->redirects);
                execute_builtin(cmdtable, data);
                exit(data->state.last_exit_status);
            }
            else if (pid > 0)
            {  // Parent process
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status))
                    data->state.last_exit_status = WEXITSTATUS(status);
            }
            else
                perror("fork");  // Handle fork failure
        }
        free_split(envp);
        return;
    }


    pid_t pid = fork();
    if (pid == 0)
	{  // Child process
		if (data->redirects != NULL)
		{
            t_redirection *redir = data->redirects;
            while (redir)
            {
                // Check if it is a here-doc redirection
                if (redir->type == 3) // Assuming 3 represents the `<<` type
                {
                    int heredoc_fd = handle_here_doc(redir); // Get the file descriptor for heredoc
                    if (heredoc_fd != -1)
                    {
                        // Redirect stdin to the output of the here-doc
                        dup2(heredoc_fd, STDIN_FILENO);
                        close(heredoc_fd); // Close after duplicating to stdin
                    }
                }
                redir = redir->next;
            }
            // Now handle other redirections
            setup_redirection(data->redirects);
			//printf("Redirections are present.\n");
			//setup_redirection(data->redirects);
		}
		else
			printf("no redirections. \n");
        // Redirection setup should be added here if applicable
        char *cmd_path = NULL;
        if (cmdtable->cmds[0] == '/')
            cmd_path = ft_strdup(cmdtable->cmds);  // Use the absolute path directly
		else
            cmd_path = get_command_path(cmdtable->cmds);  // Find the command in the PATH

        if (cmd_path)
		{
            execve(cmd_path, cmdtable->args, envp);
            perror("execve"); // If execve fails
            free(cmd_path);
        }
		else
		{
            ft_putstr_fd("Command not found: ", STDERR_FILENO);
            ft_putstr_fd(cmdtable->cmds, STDERR_FILENO);
            ft_putstr_fd("\n", STDERR_FILENO);
        }
        exit(127); // Exit with command not found status
    }
	else if (pid > 0)
	{  // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            data->state.last_exit_status = WEXITSTATUS(status);
    }
	else
        perror("fork");  // Handle fork failure
    free_split(envp); // Free environment pointer array
}



int	execute_command(t_data *data)
{
	t_command	*cmdtable;

	cmdtable = data->commands;
	if (cmdtable->next != NULL) // means theres a pipe
	{
		handle_pipe(data);
		// cmdtable = cmdtable->next;
		// from what i understand: run first command, fork the process,
		// fork will come back to execute_command at some point and check again if theres another pipe or a redirect
		return (0);
	}

	send_command(data);
	return (data->state.last_exit_status);
}
