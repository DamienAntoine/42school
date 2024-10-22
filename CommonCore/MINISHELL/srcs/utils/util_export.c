#include "../../headers/minishell.h"

void	sorted_insert(t_env **sorted_list, t_env *new_node)
{
	t_env	*current;

	if (!(*sorted_list) || strcmp((*sorted_list)->type, new_node->type) >= 0)
	{
		new_node->next = *sorted_list;
		*sorted_list = new_node;
	}
	else
	{
		current = *sorted_list;
		while (current->next && strcmp(current->next->type, new_node->type) < 0)
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

t_env	*clone_node(t_env *node)
{
	t_env	*new_node;

	if (node == NULL)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->type = node->type;
	new_node->value = node->value;
	new_node->next = NULL;
	return (new_node);
}

void	update_existing_var(t_env *current, char *new_value, t_data *data)
{
	free(current->value);
	current->value = ft_strdup(new_value);
	if (current->value == NULL)
	{
		perror("Memory allocation failed for value");
		data->state.last_exit_status = 1;
	}
	else
		data->state.last_exit_status = 0;
}

int	create_new_var(t_env **current, char *name, char *new_value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Failed to allocate memory for new environment variable");
		return (1);
	}
	new_node->type = ft_strdup(name);
	new_node->value = ft_strdup(new_value);
	new_node->next = NULL;
	if (!new_node->type || !new_node->value)
	{
		free(new_node->type);
		free(new_node->value);
		free(new_node);
		return (1);
	}
	*current = new_node;
	return (0);
}

void	export_with_arg(t_env **env_list, char *arg, t_data *data)
{
	char	*name;
	char	*new_value;
	t_env	**current;

	name = ft_strtok(arg, "=");
	new_value = ft_strtok(NULL, "");
	if (new_value == NULL)
		new_value = "";
	current = env_list;
	while (*current && ft_strcmp((*current)->type, name) != 0)
		current = &(*current)->next;
	if (*current)
		update_existing_var(*current, new_value, data);
	else
	{
		if (create_new_var(current, name, new_value))
			data->state.last_exit_status = 1;
		else
			data->state.last_exit_status = 0;
	}
}
