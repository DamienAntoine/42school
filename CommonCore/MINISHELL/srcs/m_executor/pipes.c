#include "../../headers/minishell.h"

void	handle_pipe(t_data *data)
{
	t_command	*cmdtable;
	pid_t		pid;
	int			fd[2];
	int			previous_fd;

	previous_fd = -1;
	// reset cmdtable to the start
	cmdtable = data->commands;

	while (cmdtable)
	{
		if (cmdtable->next)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();//create child
		if (pid == -1)//error value of fork
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // child
		{
			printf("child created with pid %d\n", getpid());
			if (previous_fd != -1)
			{
				dup2(previous_fd, STDIN_FILENO);
				close(previous_fd);
			}
			if (cmdtable->next)
			{
				dup2(fd[1], STDOUT_FILENO);
			}
			close(fd[0]);
			close(fd[1]);
			data->commands = data->commands->next;
			execute_command(data);
			free_minishell(data);
			exit(0);
		}
		else // parent
		{
			if (cmdtable->next)
				close(fd[1]);
			if (previous_fd != -1)
				close(previous_fd);
			previous_fd = fd[0];
			cmdtable = cmdtable->next;
		}
	}
	while (wait(NULL) > 0)
		;
	if (previous_fd != -1)
		close(previous_fd);
}

