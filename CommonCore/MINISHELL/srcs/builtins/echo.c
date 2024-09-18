#include "../../headers/minishell.h"

// syntax: echo <flag> <string>
void	handle_flags(t_data *data, int *i, int *n_flag)
{
	while (data->commands->args[*i] && !ft_strcmp(data->commands->args[*i],
			"-n"))
	{
		*n_flag = 1;
		(*i)++;
	}
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
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

void	print_quoted_arg(char *arg, t_data *data)
{
	char	quote_type;
	int		j;

	quote_type = arg[0];
	j = 1;
	while (arg[j] && arg[j] != quote_type)
	{
		if (quote_type == '"' && arg[j] == '$')
		{
			print_env_variable(&arg[j], data);
			while (arg[j] && arg[j] != ' ' && arg[j] != quote_type)
				j++;
		}
		else
			ft_putchar_fd(arg[j], 1);
		j++;
	}
}



void	print_escape(char *arg)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '\\' && arg[j + 1])
		{
			j++;
			if (arg[j] == 'n')
				ft_putchar_fd('\n', 1);
			else if (arg[j] == 't')
				ft_putchar_fd('\t', 1);
			else if (arg[j] == '\\')
				ft_putchar_fd('\\', 1);
			else if (arg[j] == '\'')
				ft_putchar_fd('\'', 1);
			else if (arg[j] == '\"')
				ft_putchar_fd('\"', 1);
			else
				ft_putchar_fd(arg[j], 1);
		}
		else
			ft_putchar_fd(arg[j], 1);
		j++;
	}
}

void	process_argument(char *arg, t_data *data)	//probably because of this function the program thinks the first character in double quotes is a quote,
													//so (echo "abcdefa") will print bcdef
{
	char	*content;
	char	*processed_arg;

	if (is_quote(arg[0]))
	{
		if (arg[0] == '\'')
		{
			content = ft_strdup(arg + 1);
			content[ft_strlen(content) - 1] = '\0';
			print_escape(content);
			free(content);
		}
		else if (arg[0] == '\"')
		{
			processed_arg = remove_balanced_quotes(arg);
			print_quoted_arg(processed_arg, data);
			free(processed_arg);
		}
	}
	else if (arg[0] == '$')
		print_env_variable(arg, data);
	else
		print_escape(arg);
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
		process_argument(arg, data);
		if (data->commands->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	data->state.last_exit_status = 0;
}
