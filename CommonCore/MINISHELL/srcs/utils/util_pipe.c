#include "../../headers/minishell.h"

int	is_pipe(t_data *data)
{
	t_token_list	*toklist;
	int				i;

	toklist = data->toklist;
	i = 0;
	while (toklist->tokens[i])
	{
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

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

void	close_pipes(int pipes[], int num_commands)
{
	if (num_commands <= 1)
		return ;
	close(pipes[0]);
	close(pipes[1]);
	close_pipes(&pipes[2], num_commands - 1);
}

int	create_pipes(int pipes[], int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands - 1)
	{
		if (pipe(pipes + i * 2) == -1)
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
