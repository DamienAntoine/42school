#include "../../headers/minishell.h"

void	handle_child_process(t_data *data, t_command *cmdtable, int pipes[],
		int num_commands, int i)
{
	int	j;
	int	exit_code;

	if (cmdtable->redirects != NULL)
	{
		if (setup_redirection(cmdtable->redirects) == -1)
			exit(1);
	}
	if (i > 0)
		dup2(pipes[(i - 1) * 2], STDIN_FILENO);
	if (i < num_commands - 1 && !output_redirection_exists(cmdtable->redirects))
		dup2(pipes[i * 2 + 1], STDOUT_FILENO);
	j = 0;
	while (j < num_commands - 1)
	{
		close(pipes[j * 2]);
		close(pipes[j * 2 + 1]);
		j++;
	}
	data->commands = cmdtable;
	exit_code = send_command(data);
	free_minishell(data);
	exit(exit_code);
}

int	setup_pipes_and_fork(t_data *data, t_command *cmdtable, int pipes[],
		pid_t *child_pids)
{
	pid_t	pid;
	int		num_commands;
	int		i;

	num_commands = ft_cmdsize(cmdtable);
	if (create_pipes(pipes, num_commands) == -1)
		return (-1);
	i = 0;
	while (i < num_commands)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (pid == 0)
			handle_child_process(data, cmdtable, pipes, num_commands, i);
		else
			child_pids[i] = pid;
		cmdtable = cmdtable->next;
		i++;
	}
	return (0);
}

int	handle_pipes(t_data *data, t_command *cmdtable, int num_commands)
{
	int		*pipes;
	pid_t	*child_pids;
	int		exit_code;
	int		i;

	pipes = malloc((num_commands - 1) * 2 * sizeof(int));
	child_pids = malloc(num_commands * sizeof(pid_t));
	if (!pipes || !child_pids)
	{
		free(pipes);
		free(child_pids);
		return (-1);
	}
	exit_code = 0;
	if (setup_pipes_and_fork(data, cmdtable, pipes, child_pids) == -1)
	{
		free(pipes);
		free(child_pids);
		return (-1);
	}
	i = 0;
	while (i < (num_commands - 1) * 2)
		close(*(pipes + i++));
	exit_code = wait_for_children(data, child_pids, num_commands);
	free(pipes);
	free(child_pids);
	return (exit_code);
}
