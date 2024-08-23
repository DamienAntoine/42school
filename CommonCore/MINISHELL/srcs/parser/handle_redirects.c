#include "../../headers/minishell.h"

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

void ft_add_redirection(t_command *current, char *file, int type)
{
	t_redirection *redir;

	redir = ft_create_redirection(file, type);
	if (!redir)
		return;
	if (current->redirections == NULL)
		current->redirections = redir;
	else
	{
		t_redirection *tmp = current->redirections;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}
