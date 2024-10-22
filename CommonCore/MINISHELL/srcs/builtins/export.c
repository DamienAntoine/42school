
#include "../../headers/minishell.h"

static void	sorted_insert(t_env **sorted_list, t_env *new_node)
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

static t_env	*clone_node(t_env *node)
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

void	move_current(t_env *current)
{
	while (current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->type, 1);
		if (current->value && *current->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
}

void	print_export(t_env *env_list, t_data *data)
{
	t_env	*current;
	t_env	*sorted_list;
	t_env	*new_node;

	current = env_list;
	sorted_list = NULL;
	while (current)
	{
		new_node = clone_node(current);
		if (new_node)
			sorted_insert(&sorted_list, new_node);
		current = current->next;
	}
	current = sorted_list;
	move_current(current);
	while (sorted_list)
	{
		current = sorted_list;
		sorted_list = sorted_list->next;
		free(current);
	}
	data->state.last_exit_status = 0;
}

static void	update_existing_var(t_env *current, char *new_value, t_data *data)
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

static int	create_new_var(t_env **current, char *name, char *new_value)
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

static void	export_with_arg(t_env **env_list, char *arg, t_data *data)
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

int	is_valid_arg(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	handle_export(t_data *data)
{
	int	i;

	i = 0;
	if (data->toklist->token_count == 1)
		print_export(data->env, data);
	else
	{
		while (data->commands->args[i])
		{
			if (!is_valid_arg(data->commands->args[i]))
			{
				ft_putstr_fd("export: `", STDERR_FILENO);
				ft_putstr_fd(data->commands->args[i], STDERR_FILENO);
				ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
				data->state.last_exit_status = 1;
				exit(data->state.last_exit_status);
			}
			else
				export_with_arg(&data->env, data->commands->args[i], data);
			i++;
		}
	}
	return (0);
}
