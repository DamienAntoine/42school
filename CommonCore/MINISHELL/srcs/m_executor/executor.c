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
		ft_exit(data);
	/* 	if (data->toklist->token_count == 1)
			ft_exit(data, 0);
		else
			ft_exit(data, ft_atoi(data->toklist->tokens[1])); */
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
	char		**envp = env_list_to_array(data->env);
	t_command	*cmdtable = data->commands;
	pid_t		pid;
	int			status;

	if (!cmdtable || !cmdtable->cmds || !cmdtable->args[0])
	{
		ft_putstr_fd("No command provided\n", STDERR_FILENO);
		free_split(envp);
		data->state.last_exit_status = 127;
		return;
	}

	if (is_builtin(cmdtable->cmds))
	{
		if (data->redirects == NULL) //if no redirections
			execute_builtin(cmdtable, data); //only execute the builtin
		else //if redirections
		{
			//fork process
			pid = fork();
			if (pid == 0)//child
			{
				printf("Built-in command with redirection.\n");
				setup_redirection(data->redirects);
				execute_builtin(cmdtable, data);
				exit(data->state.last_exit_status);
			}
			else if (pid > 0)//parent
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					set_exit_status(WEXITSTATUS(status), data);
				else if (WIFSIGNALED(status))
					set_exit_status(128 + WTERMSIG(status), data);
				else
					set_exit_status(status, data);
			}
			else
			{
				perror("fork");//if fork failed
				data->state.last_exit_status = 1;
			}
		}
		free_split(envp);
		return;
	}


	t_redirection	*redir;
	char			*cmd_path;
	int				heredoc_fd;

	pid = fork();
	if (pid == 0)//child process
	{
		if (data->redirects != NULL)
		{
			redir = data->redirects;
			while (redir)
			{
				// check if it is a here-doc redirection
				if (redir->type == 3) //3 = `<<` type
				{
					heredoc_fd = handle_here_doc(redir); //get the fd for heredoc
					if (heredoc_fd != -1)
					{
						//redirect stdin to the output of the here-doc
						dup2(heredoc_fd, STDIN_FILENO);
						close(heredoc_fd); // Close after duplicating to stdin
					}
				}
				redir = redir->next;
			}
			//handle other redirections
			setup_redirection(data->redirects);
		}
		// Redirection setup should be added here if applicable
		cmd_path = NULL;
		if (cmdtable->cmds[0] == '/')
			cmd_path = ft_strdup(cmdtable->cmds);//use absolute path
		else
			cmd_path = get_command_path(cmdtable->cmds);//find command in PATH
		if (cmd_path)
		{
			execve(cmd_path, cmdtable->args, envp);
			perror("execve");
			free(cmd_path);
		}
		else
		{
			ft_putstr_fd("Command not found: ", STDERR_FILENO);
			ft_putstr_fd(cmdtable->cmds, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		exit(127);//Exit with command not found status
	}
	else if (pid > 0)//parent
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status), data);
		else if (WIFSIGNALED(status))
			set_exit_status(128 + WTERMSIG(status), data);
		else
			set_exit_status(status, data);
	}
	else{
		perror("fork");
		data->state.last_exit_status = 1;
	}
	free_split(envp);
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

