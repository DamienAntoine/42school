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
		pipe(fd);// initialize fd variable (fd[1] is used to send inputs to the pipe (write), and fd[0] to retrieve the input(read))
		pid = fork();//create new process (child process)


		//this will be true for childs (fork() returns 0 to child processes)
		if (pid == 0)
		{
			if (previous_fd != -1)
			{
				dup2(previous_fd, STDIN_FILENO);
				close(previous_fd);
			}

			if (cmdtable->next)
				dup2(fd[1], STDOUT_FILENO);// dup2: duplicate a file descriptor. this (should) redirect the output from before the pipe to the command after the pipe
			close(fd[0]);
			close(fd[1]);
			execute_command(data);//send the child back to execute function, and execute the new command (after the pipe), while also checking if theres another pipe or a redirection
			exit(0);//KILL THE CHILD
		}

		//and this will be true for parent (main process)
		else if (pid > 0)
		{
			close(fd[1]); // close parent pipe (write)
			if (previous_fd != -1)
				close(previous_fd);//close previous read
			previous_fd = fd[0];//update previous read to current read
			cmdtable = cmdtable->next;
		}
		else
		{
			perror("fork error in pipe function");
			exit(EXIT_FAILURE);
		}
	}
	while (wait(NULL) > 0);
}
