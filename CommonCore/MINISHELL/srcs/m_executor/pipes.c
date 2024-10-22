#include "../../headers/minishell.h"

int	output_redirection_exists(t_redirection *redirects)
{
	while (redirects)
	{
		if (redirects->type == 1 || redirects->type == 2)
			return (1);
		redirects = redirects->next;
	}
	return (0);
}

void	close_pipes(int pipes[][2], int num_commands)
{
	if (num_commands <= 1)
		return ;
	close(pipes[0][0]);
	close(pipes[0][1]);
	close_pipes(&pipes[1], num_commands - 1);
}

int	create_pipes(int pipes[][2], int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	wait_for_children(t_data *data, pid_t *child_pids, int num_commands)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < num_commands)
	{
		if (waitpid(child_pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit_code = 1;
		}
		if (WIFEXITED(status))
		{
			data->state.last_exit_status = WEXITSTATUS(status);
			if (WEXITSTATUS(status) != 0)
				exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}

void	handle_child_process(t_data *data, t_command *cmdtable, int pipes[][2],
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
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_commands - 1 && !output_redirection_exists(cmdtable->redirects))
		dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < num_commands - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	data->commands = cmdtable;
	exit_code = send_command(data);
	free_minishell(data);
	exit(exit_code);
}

int	setup_pipes_and_fork(t_data *data, t_command *cmdtable, int pipes[][2],
		int num_commands, pid_t *child_pids)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (create_pipes(pipes, num_commands) == -1)
		return (-1);
	while (i < num_commands)
	{
		if ((pid = fork()) == -1)
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
	int		pipes[num_commands - 1][2];
	pid_t	child_pids[num_commands];
	int		exit_code;

	exit_code = 0;
	if (setup_pipes_and_fork(data, cmdtable, pipes, num_commands, child_pids) ==
		-1)
		return (-1);
	close_pipes(pipes, num_commands);
	exit_code = wait_for_children(data, child_pids, num_commands);
	return (exit_code);
}
