#include "../../headers/minishell.h"

// FIX FOR MULTIPLE ARGS  like unset AAAAA BBBBB+



// use to unset a variable (like raja showed with "unset pwd")
static void	unset_env_var(t_env **env_list, char *name)
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->type, name) == 0)
			// goes through every nodes until it finds the target
		{
			if (!previous) // if there is no node before Current, means its the first node of the list
				*env_list = current->next;
			else
				previous->next = current->next; // theres a node before current,
			free(current->type);                // free name
			free(current->value);               // free value
			free(current);                      // free node
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void    handle_unset(t_env **lst, char **args)
{
    int i;
    i = 1;
    while (args[i])
        unset_env_var(lst, args[i++]);
}