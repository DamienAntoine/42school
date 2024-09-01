#include "../../headers/minishell.h"

void	send_command(t_data *data)
		// need to change the parameters sent to builtins depenting on their needs
{
	char	**envp = env_list_to_array(data->env);
	t_command *cmdtable;
	pid_t pid;

	cmdtable = data->commands;
	if (ft_strcmp(cmdtable->cmds, "cd") == 0)
	{
		ft_cd(cmdtable);
		// check if argument is a folder (or should we check this inside the builtin file to make it more clear)
	}

	else if (ft_strcmp(cmdtable->cmds, "echo") == 0)
		ft_echo(data->toklist);

	else if (ft_strcmp(cmdtable->cmds, "env") == 0)
		ft_env(data->env);

	else if (ft_strcmp(cmdtable->cmds, "exit") == 0)
		ft_exit(data, ft_atoi(data->toklist->tokens[1]));

	else if (ft_strcmp(cmdtable->cmds, "export") == 0)
	{
		if (data->toklist->token_count == 1)
			print_export(data->env);
		else
			handle_export(&data->env, data->toklist->tokens);
		//	export_with_arg(&data->env, data->toklist->tokens[1]);

	}
		
	else if (ft_strcmp(cmdtable->cmds, "pwd") == 0)
		ft_pwd(data->env);

	else if (ft_strcmp(cmdtable->cmds, "unset") == 0)
		handle_unset(&data->env, data->toklist->tokens);
		//unset_env_var(&data->env, cmdtable->args[0]);

	else // Handle non-builtins
	{
		pid = fork();
		if (pid == 0) // child
		{
			execve(cmdtable->cmds, cmdtable->args, envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else                       // parent
			waitpid(pid, NULL, 0); // Wait for the child process to finish
	}
}



int	execute_command(t_data *data)
{
	/*
	t_command *cmdtable;

	cmdtable = data->commands;
	
	if (cmdtable->next != NULL) // means theres a pipe
	{
		handle_pipe(data);
		// from what i understand: run first command, fork the process,
		// fork will come back to execute_command at some point and check again if theres another pipe or a redirect
		return (0);
	}
	if (cmdtable->redirections >= 0 && cmdtable->redirections <= 3)
	{
		handle_redirection(data);
		return (0);
	}
	*/
	// no pipe, just check command syntax and execute
	send_command(data);
	return (0);
}