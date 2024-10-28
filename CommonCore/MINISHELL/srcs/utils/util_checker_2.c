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
			fd = open_redirection(redir);
			if (fd == -1)
			{
				perror(redir->file);
				return (-1);
			}
			if (redir->type != 3)
				close(fd);
			redir = redir->next;
		}
		cmdtable = cmdtable->next;
	}
	return (0);
}
