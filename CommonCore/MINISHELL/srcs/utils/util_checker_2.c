/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_checker_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:17:34 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:17:34 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_all_pipes(int *pipes)
{
	int	j;

	j = 0;
	while (pipes[j] != -1)
		close(pipes[j++]);
}

int	check_redirection_before_fork(t_data *data)
{
	t_command		*cmdtable;
	int				fd;
	t_redirection	*redir;

	cmdtable = data->commands;
	while (cmdtable)
	{
		redir = cmdtable->redirects;
		while (redir)
		{
			if (redir->type != 3)
			{
				fd = open_redirection(redir);
				if (fd == -1)
				{
					perror(redir->file);
					return (-1);
				}
				close(fd);
			}
			redir = redir->next;
		}
		cmdtable = cmdtable->next;
	}
	return (0);
}
