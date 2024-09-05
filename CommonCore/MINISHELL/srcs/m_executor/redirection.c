#include "../../headers/minishell.h"

void	handle_redirection(t_data *data)
{
	if (data->redirects->type == 0)
	{
		//'<'
	}
	else if (data->redirects->type == 1)
	{
		//'>'
	}
	else if (data->redirects->type == 2)
	{
		//'>>'
	}
	else if (data->redirects->type == 3)
	{
		//'<<'
	}
}


t_redirection *ft_create_redirection(char *file, int type)
{
	t_redirection *redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(file);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

void ft_add_redirection(t_data *data, char *file, int type)
{
	t_redirection *redir;
    t_redirection *tmp;

	redir = ft_create_redirection(file, type);
	if (!redir)
		return;
	if (data->redirects == NULL)
		data->redirects = redir;
	else
	{
		tmp = data->redirects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}
