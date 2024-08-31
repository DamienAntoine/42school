#include "../../headers/minishell.h"

int	execute_command(t_data *data)
{
	t_command	*cmdtable;

	cmdtable = data->commands;
	if (cmdtable->next != NULL)//means theres a pipe
	{
		handle_pipe(data);
		//from what i understand: run first command, fork the process,
		//fork will come back to execute_command at some point and check again if theres another pipe or a redirect
		return (0);
	}
	if (cmdtable->redirections >= 0 && cmdtable->redirections <= 3)
	{
		handle_redirection(data);
		return (0);
	}
	//no pipe, just check command syntax and execute
	send_command(data);
	return (0);
}

void	handle_pipe(t_data *data)
{
	t_command	*cmdtable = data->commands;
	pid_t		pid;
	int			fd[2];
	int			previous_fd;

	previous_fd = -1;
	while (cmdtable)
	{
		pipe(fd);//initializes fd variable: fd[0] becomes file descriptor for reading from the pipe and fd[1] the FD for writing data into the pipe
		pid = fork();
		if (previous_fd == -1)
		{
			dup2(previous_fd, STDIN_FILENO);
			close(previous_fd);
		}
	}
}

void	handle_redirection(t_data *data)
{
	if (data->commands->redirections->type == 0)
	{
		//'<'
	}
	else if (data->commands->redirections->type == 1)
	{
		//'>'
	}
	else if (data->commands->redirections->type == 2)
	{
		//'>>'
	}
	else if (data->commands->redirections->type == 3)
	{
		//'<<'
	}
}

void	send_command(t_data *data) //need to change the parameters sent to builtins depenting on their needs
{
	if (ft_strcmp(data->commands->cmds, "cd") == 0)
	{
		ft_cd(data->commands);
		//check if argument is a folder (or should we check this inside the builtin file to make it more clear)
	}

	else if (ft_strcmp(data->commands->cmds, "echo") == 0)
		ft_echo(data->commands->args);

	else if (ft_strcmp(data->commands->cmds, "env") == 0)
		ft_env(data->env);

	else if (ft_strcmp(data->commands->cmds, "exit") == 0)
		ft_exit();

	else if (ft_strcmp(data->commands->cmds, "export") == 0)
		ft_export(data);

	else if (ft_strcmp(data->commands->cmds, "pwd") == 0)
		ft_pwd(data->env);

	else if (ft_strcmp(data->commands->cmds, "unset") == 0)
		ft_unset(data->env);
}
