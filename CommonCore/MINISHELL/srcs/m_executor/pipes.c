#include "../../headers/minishell.h"

void	handle_pipe(t_data *data, int num_commands)
{
	t_command	*cmdtable;
	int			pipes[num_commands - 1][2];
	pid_t		pid;
	int			status;
	int			i;
	int			j;

	cmdtable = data->commands;

	// create pipes
	i = 0;
	while (i < num_commands - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}

	// creates fork for every command in the pipeline
	i = 0;
	while (i < num_commands)
	{
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // child process
		{
			if (i > 0)// set input from previous pipe if not first command
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < num_commands - 1)// set output to next pipe if not last command
				dup2(pipes[i][1], STDOUT_FILENO);

			// close all pipes (child)
			j = 0;
			while(j < num_commands - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}

			// exec cmd
			data->commands = cmdtable; // pass the current command to execute
			send_command(data);
			free_minishell(data);
			exit(EXIT_FAILURE);        // kill childprocess if command fails
		}
		cmdtable = cmdtable->next; // move to the next command
		i++;
	}

	// close all pipes (parent)
	i = 0;
	while (i < num_commands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}

	// wait for childs to die
	i = 0;
	while (i < num_commands)
	{
		wait(&status);
		if (WIFEXITED(status))
			data->state.last_exit_status = WEXITSTATUS(status);
		i++;
	}
}
