#include "../../headers/minishell.h"

// init (when starting minishell)
// to print with the env cmd, just go through every node and print "NAME"+"="+"value"+newline
void	init_env(char **env, t_env **cur_env)
{
	int		i;
	char	**temp;
	t_env	*new_node;
	t_env	*last_node;

	i = 0;
	*cur_env = NULL; // init linked list
	while (env[i])
	{
		temp = ft_split(env[i], '=');
		new_node = (t_env *)malloc(sizeof(t_env)); // new node
		if (!new_node)
			return ;
		new_node->type = strdup(temp[0]);  // copy var name
		new_node->value = strdup(temp[1]); // copy value
		new_node->next = NULL;
		// if first node (first loop)
		if (*cur_env == NULL)
			*cur_env = new_node;
		else
		{
			last_node = *cur_env;
			// go to end of list and add new node (i think theres smth in libft for that)
			while (last_node->next)
				last_node = last_node->next;
			last_node->next = new_node;
		}
		free(temp[0]);
		free(temp[1]);
		free(temp);
		i++;
	}
}

// use this to update an env variable (after cd for example to update PWD), instead of running init again which would reset the whole env
void	update_env_variable(t_env *env_list, char *name, char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->type, name) == 0)
		{
			free(current->value);           // free old value
			current->value = ft_strdup(value); // set new value
			return ;
		}
		current = current->next;
	}
}

char	*find_env_value(t_env *env, const char *name)
{
	while (env != NULL)
	{
		if (!ft_strcmp(env->type, name))
			return (env->value);
		env = env->next;
	}
	return (NULL); // Return NULL if the variable is not found
}
