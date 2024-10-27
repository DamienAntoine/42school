#include "../../headers/minishell.h"

void	handle_child_process(t_data *data, t_command *cmdtable, int pipes[],
		int i)
{
	int	j;
	int	exit_code;

	j = 0;
	if (cmdtable->redirects != NULL)
	{
		if (setup_redirection(cmdtable->redirects) == -1)
			exit(1);
	}
	if (i > 0)
		dup2(pipes[(i - 1) * 2], STDIN_FILENO);
	if (cmdtable->next && !output_redirection_exists(cmdtable->redirects))
		dup2(pipes[i * 2 + 1], STDOUT_FILENO);
	while (pipes[j] != -1)
	{
		close(pipes[j]);
		j++;
	}
	data->commands = cmdtable;
	exit_code = send_command(data);
	free_minishell(data);
	exit(exit_code);
}

int	initialize_pipes(int *pipes, t_command *cmdtable)
{
	int	num_commands;

	num_commands = ft_cmdsize(cmdtable);
	if (create_pipes(pipes, num_commands) == -1)
		return (-1);
	pipes[(num_commands - 1) * 2] = -1;
	return (0);
}

int	fork_and_setup_children(t_data *data, t_command *cmdtable, int *pipes,
		pid_t *child_pids)
{
	pid_t	pid;
	int		i;
	int		num_commands;

	i = 0;
	num_commands = ft_cmdsize(cmdtable);
	while (i < num_commands)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (pid == 0)
			handle_child_process(data, cmdtable, pipes, i);
		else
			child_pids[i] = pid;
		cmdtable = cmdtable->next;
		i++;
	}
	close_all_pipes(pipes);
	return (0);
}

int	setup_pipes_and_fork(t_data *data, t_command *cmdtable, int *pipes,
		pid_t *child_pids)
{
	if (initialize_pipes(pipes, cmdtable) == -1)
		return (-1);
	if (fork_and_setup_children(data, cmdtable, pipes, child_pids) == -1)
		return (-1);
	return (0);
}

int	handle_pipes(t_data *data, t_command *cmdtable, int num_commands)
{
	int		*pipes;
	pid_t	*child_pids;
	int		exit_code;

	pipes = malloc(((num_commands - 1) * 2 + 1) * sizeof(int));
	child_pids = malloc(num_commands * sizeof(pid_t));
	if (!pipes || !child_pids || setup_pipes_and_fork(data, cmdtable, pipes,
			child_pids) == -1)
	{
		free(pipes);
		free(child_pids);
		return (-1);
	}
	exit_code = wait_for_children(data, child_pids, num_commands);
	free(pipes);
	free(child_pids);
	return (exit_code);
}
