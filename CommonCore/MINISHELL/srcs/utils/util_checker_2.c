#include "../../headers/minishell.h"

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
