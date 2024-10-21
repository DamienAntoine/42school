#include "../../headers/minishell.h"

void	init_env(char **env, t_env **cur_env)
{
	int		i;
	char	*equal_sign;
	t_env	*new_node;
	t_env	*last_node;

	i = 0;
	new_node = NULL;
	last_node = NULL;
	*cur_env = NULL;
	while (env[i])
	{
		equal_sign = strchr(env[i], '=');
		if (!equal_sign) 
		{
			i++;
			continue ;
		}
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
		{
			perror("failed to allocate memory for new env var");
			free_env_list(*cur_env);
			exit(EXIT_FAILURE);
		}
		new_node->type = ft_substr(env[i], 0, equal_sign - env[i]);
		new_node->value = ft_strdup(equal_sign + 1);
		new_node->next = NULL;
		if (!new_node->type || !new_node->value)
		{
			free(new_node->type);
			free(new_node->value);
			free(new_node);
			free_env_list(*cur_env);
			exit(EXIT_FAILURE);
		}
		if (*cur_env == NULL)
			*cur_env = new_node;
		else
			last_node->next = new_node;
		last_node = new_node;
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
			free(env->value);
			env->value = ft_strdup(value);
			return;
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


char *find_env_value(t_env *env, const char *name)
{
	if (!env || !name)
		return NULL;

	while (env != NULL)
	{
		if (!ft_strcmp(env->type, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}


