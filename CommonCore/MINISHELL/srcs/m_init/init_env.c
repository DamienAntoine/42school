#include "../../headers/minishell.h"

void init_env(char **env, t_env **cur_env)
{
    int i;
    t_env *new_node;

    i = 0;
    new_node = NULL;
    *cur_env = NULL;
    while (env[i])
    {
        new_node = create_new_node(env[i]);
        if (!new_node)
        {
            free_env_list(*cur_env);
            exit(EXIT_FAILURE);
        }
        add_node_to_list(cur_env, new_node);
        i++;
    }
}

void	up_env(t_env **env_list, const char *name, const char *value)
{
	t_env	*env;
	t_env	*new_node;

	env = *env_list;
	while (env != NULL)
	{
		if (ft_strcmp(env->type, name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_node = malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->type = ft_strdup(name);
		new_node->value = ft_strdup(value);
		new_node->next = *env_list;
		*env_list = new_node;
	}
}

char	*find_env_value(t_env *env, const char *name)
{
	if (!env || !name)
		return (NULL);
	while (env != NULL)
	{
		if (!ft_strcmp(env->type, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
