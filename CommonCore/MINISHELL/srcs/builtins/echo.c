#include "../../headers/minishell.h"

int	ft_echo(t_data *data)
{
	int		n_flag;
	int		i;
	char	*arg;

	n_flag = 0;
	i = 0;
	handle_flags(data, &i, &n_flag);
	while (data->commands->args[i])
	{
		arg = data->commands->args[i];
		print_escape(arg);
		if (data->commands->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	data->state.last_exit_status = 0;
	return (0);
}
