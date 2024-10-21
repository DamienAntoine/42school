#include "../../headers/minishell.h"

static void	unset_env_var(t_env **env_list, char *name)
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->type, name) == 0)
		{
			if (!previous)
				*env_list = current->next;
			else
				previous->next = current->next;
			free(current->type);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	handle_unset(t_env **lst, char **args)
{
	int	i;

	i = 1;
	while (args[i])
		unset_env_var(lst, args[i++]);
	return (0);
}
