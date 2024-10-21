
#include "../../headers/minishell.h"

static void sorted_insert(t_env **sorted_list, t_env *new_node) {
    if (!(*sorted_list) || strcmp((*sorted_list)->type, new_node->type) >= 0) {
        new_node->next = *sorted_list;
        *sorted_list = new_node;
    } else {
        t_env *current = *sorted_list;
        while (current->next && strcmp(current->next->type, new_node->type) < 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

static t_env *clone_node(t_env *node) {
    if (node == NULL) return NULL;
    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node) return NULL;
    new_node->type = node->type; 
    new_node->value = node->value;
    new_node->next = NULL;
    return new_node;
}

void print_export(t_env *env_list, t_data *data) {
    t_env *current = env_list;
    t_env *sorted_list = NULL;
    t_env *new_node;

    while (current) {
        new_node = clone_node(current);
        if (new_node) {
            sorted_insert(&sorted_list, new_node);
        }
        current = current->next;
    }
    current = sorted_list;
    while (current) {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(current->type, 1);
        if (current->value && *current->value) {
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(current->value, 1);
            ft_putstr_fd("\"", 1);
        }
        ft_putchar_fd('\n', 1);
        current = current->next;
    }
    while (sorted_list) {
        current = sorted_list;
        sorted_list = sorted_list->next;
        free(current); 
    }
    data->state.last_exit_status = 0;
}

static void export_with_arg(t_env **env_list, char *arg, t_data *data)
{
    char *name = ft_strtok(arg, "=");
    char *new_value = ft_strtok(NULL, "");

    if (new_value == NULL)
        new_value = "";  
    t_env **current = env_list;
    while (*current && ft_strcmp((*current)->type, name) != 0) {
        current = &(*current)->next;
    }

    if (*current)
    {
        free((*current)->value);
        (*current)->value = ft_strdup(new_value);
        if ((*current)->value == NULL) {
            perror("Memory allocation failed for value");
            data->state.last_exit_status  = 1;  
            return;
        }
        data->state.last_exit_status = 0;  
    }
    else
    {
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node) {
            perror("Failed to allocate memory for new environment variable");
            data->state.last_exit_status = 1;  
            return;
        }
        new_node->type = ft_strdup(name);
        new_node->value = ft_strdup(new_value);
        new_node->next = NULL;

        if (new_node->type == NULL || new_node->value == NULL) {
            free(new_node->type);  
            free(new_node->value);
            free(new_node);
            data->state.last_exit_status =  1; 
            return;
        }

        *current = new_node; 
        data->state.last_exit_status =  0; 
    }
}


int is_valid_arg(const char *arg)
{
	int i = 0;

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
	int i;
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
