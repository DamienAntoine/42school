#include "../../headers/minishell.h"

void	handle_pipe(t_data *data, int num_commands)
{
	t_command	*cmdtable;
	int			pipes[num_commands - 1][2]; // -1 because there's always -1 pipes for the number of commands
	pid_t		pid;
	pid_t		wpid;
	int			status;
	int			i;
	int			j;

	cmdtable = data->commands;

	// Create pipes
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

	// Create fork for every command in the pipeline
	i = 0;
	while (i < num_commands)
	{
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // Child process
		{
			if (i > 0) // If not first command
				dup2(pipes[i - 1][0], STDIN_FILENO); // Set input from previous pipe
			if (i < num_commands - 1) // If not last command
				dup2(pipes[i][1], STDOUT_FILENO); // Set output to next pipe

			// Close all pipes except the ones used
			for (j = 0; j < num_commands - 1; j++)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}

			// Execute command
			data->commands = cmdtable; // Pass the current command to execute
			int exec_status = send_command(data); // Capture the command's exit status
			free_minishell(data);
			exit(exec_status); // Exit with the command's exit status
		}
		cmdtable = cmdtable->next; // Move to the next command
		i++;
	}

	// Close all pipes in the parent
	i = 0;
	while (i < num_commands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}

	// Wait for children to die
	i = 0;
	while (i < num_commands)
	{
		wpid = wait(&status);
		if (wpid == -1)
		{
			perror("wait");
			continue;
		}
		if (WIFEXITED(status))
			data->state.last_exit_status = WEXITSTATUS(status);
		i++;
	}
}
