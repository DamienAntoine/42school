#include "../../headers/minishell.h"

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
