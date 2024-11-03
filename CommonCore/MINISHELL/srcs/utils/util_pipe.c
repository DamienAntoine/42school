/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:14:08 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 15:24:01 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
