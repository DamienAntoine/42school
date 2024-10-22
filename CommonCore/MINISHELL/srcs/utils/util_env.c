#include "../../headers/minishell.h"

void	free_new_node(t_env *new_node)
{
	if (new_node)
	{
		free(new_node->type);
		free(new_node->value);
		free(new_node);
	}
}

t_env	*create_new_node(const char *env_entry)
{
	t_env	*new_node;
	char	*equal_sign;

	equal_sign = strchr(env_entry, '=');
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("failed to allocate memory for new env var");
		return (NULL);
	}
	new_node->type = ft_substr(env_entry, 0, equal_sign - env_entry);
	new_node->value = ft_strdup(equal_sign + 1);
	new_node->next = NULL;
	if (!new_node->type || !new_node->value)
	{
		free_new_node(new_node);
		return (NULL);
	}
	return (new_node);
}

void	add_node_to_list(t_env **cur_env, t_env *new_node)
{
	t_env	*last_node;

	if (*cur_env == NULL)
		*cur_env = new_node;
	else
	{
		last_node = *cur_env;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}
