#include "../../headers/minishell.h"

// init (when starting minishell)
// to print with the env cmd,
	//just go through every node and print "NAME"+"="+"value"+newline
void	init_env(char **env, t_env **cur_env)
{
	int		i;
	char	**temp;
	t_env	*new_node;
	t_env	*last_node;

	i = 0;
	*cur_env = NULL;
	while (env[i])
	{
		temp = ft_split(env[i], '=');
		if (!temp || !temp[0] || !temp[1])
		{
			if (temp)
				free_split(temp);
			i++;
			continue ;
		}
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
		{
			perror("failed to allocate memory for new env var");
			free_split(temp);
			exit(EXIT_FAILURE);
		}
		new_node->type = ft_strdup(temp[0]);
		new_node->value = ft_strdup(temp[1]);
		new_node->next = NULL;
		if (!new_node->type || !new_node->value)
		{
			free(new_node->type);
			free(new_node->value);
			free(new_node);
			free_split(temp);
			exit(EXIT_FAILURE);
		}
		if (*cur_env == NULL)
			*cur_env = new_node;
		else
			last_node->next = new_node;
		last_node = new_node;
		free_split(temp);
		i++;
	}
}

void update_or_add_env_variable(t_env **env_list, const char *name, const char *value) 
{
    t_env	*env;
	t_env	*new_node;
	env = *env_list;
    while (env != NULL) 
	{
        if (ft_strcmp(env->type, name) == 0) {
            free(env->value); // Free the old value
            env->value = ft_strdup(value); // Duplicate and assign the new value
            return;
        }
        env = env->next;
    }
    // If not found, append a new node
    new_node = malloc(sizeof(t_env));
    if (new_node) 
	{
        new_node->type = ft_strdup(name);
        new_node->value = ft_strdup(value);
        new_node->next = *env_list;
        *env_list = new_node; // Set the new node as the head of the list
    }
}


char	*find_env_value(t_env *env, const char *name)
{
	// printf("fell into find_env_value function\n");
	while (env != NULL)
	{
		//	printf("checking variable: %s\n", env->type);
		if (!ft_strcmp(env->type, name))
			return (env->value);
		env = env->next;
	}
	return (NULL); // Return NULL if the variable is not found
}
