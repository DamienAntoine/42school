#include "../../headers/minishell.h"

// syntax: echo <flag> <string>
void	handle_flags(t_data *data, int *i, int *n_flag)
{
	while (data->commands->args[*i] &&
	!ft_strcmp(data->commands->args[*i], "-n"))
	{
		*n_flag = 1;
		(*i)++;
	}
}

void	print_env_variable(char *arg, t_data *data)
{
	char	*env_type;
	char	*env_value;

	env_type = &arg[1];
	env_value = find_env_value(data->env, env_type);
	if (env_value)
		ft_putstr_fd(env_value, 1);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	print_escape(char *arg)
{
	int	j;
	int	inside_quotes;

	j = 0;
	inside_quotes = 0;
	while (arg[j])
	{
		if (arg[j] == '\\' && is_quote(arg[j + 1]))
		{
			j++;
			ft_putchar_fd(arg[j], 1);
		}
		else if (is_quote(arg[j]) && (j == 0 || arg[j - 1] != '\\'))
			inside_quotes = !inside_quotes;
		else if (arg[j] == '\\' && arg[j + 1] && !inside_quotes)
		{
			j++;
			if (arg[j] == 'n')
				ft_putchar_fd('\n', 1);
			else if (arg[j] == 't')
				ft_putchar_fd('\t', 1);
			else if (arg[j] == '\\')
				ft_putchar_fd('\\', 1);
			else
				ft_putchar_fd(arg[j], 1);
		}
		else
			ft_putchar_fd(arg[j], 1);
		j++;
	}
}

void	ft_echo(t_data *data)
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
		if (!ft_strcmp(arg, "$?"))
			ft_putnbr_fd(data->state.last_exit_status, 1);
		else if (arg[0] == '$')
			print_env_variable(arg, data);
		else
			print_escape(arg);
		if (data->commands->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	data->state.last_exit_status = 0;
}
