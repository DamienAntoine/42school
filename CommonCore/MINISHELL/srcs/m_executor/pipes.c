#include "../../headers/minishell.h"

void	handle_pipe(t_data *data)
{
	t_command	*cmdtable;
	pid_t		pid;
	int			fd[2];
	int			previous_fd;

	cmdtable = data->commands;
	previous_fd = -1;
	while (cmdtable)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe error");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) //this will be true for childs (fork() returns 0 to child processes)
		{
			printf("Child process (PID: %d):\n", getpid());	//debug
			// redirects stdin if previous_fd valid
			if (previous_fd != -1)
			{
				dup2(previous_fd, STDIN_FILENO);
				close(previous_fd);
			}
			else
				printf("No previous_fd to redirect\n");
			// redirects stdout if next command
			if (cmdtable->next)
				dup2(fd[1], STDOUT_FILENO);
			else
				printf("no more pipes\n");	//debug
			close(fd[0]);
			close(fd[1]);
			data->commands = data->commands->next;
			execute_command(data);
			free_minishell(data);
			printf("Terminating Child process (PID: %d):\n\n", getpid());	//debug
			exit(0); // kill child
		}
		else // parent
		{
			printf("In parent process:\n");
			printf("Closing fd[1] = %d\n", fd[1]);
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
	{
		printf("Closing final previous_fd = %d\n", previous_fd);
		close(previous_fd);
	}
}
