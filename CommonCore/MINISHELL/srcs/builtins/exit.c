#include "../../headers/minishell.h"

void	set_exit_status(long status, t_data *data)
{
	long	normalized_status;
	long	modulo;

	if (status >= 0)
		normalized_status = status % 256;
	else
	{
		modulo = status % 256;
		normalized_status = 256 + modulo;
		if (modulo == 0)
			normalized_status = 0;
	}
	data->state.last_exit_status = (int)normalized_status;
}

void	exit_helper(char *status_str, int status, t_data *data)
{
	status = ft_atoi(status_str);
	if (data->commands->args[1])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		set_exit_status(1, data);
	}
	else
		set_exit_status(status, data);
}

int	ft_exit(t_data *data)
{
	char	*status_str;
	int		status;

	status = 0;
	if (data->commands->args[0])
	{
		status_str = ft_strdup(data->commands->args[0]);
		if (ft_isalpha(status_str[0]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			set_exit_status(2, data);
		}
		else
			exit_helper(status_str, status, data);
		free(status_str);
	}
	else
		set_exit_status(data->state.last_exit_status, data);
	free_minishell(data);
	exit(data->state.last_exit_status);
	return (0);
}
