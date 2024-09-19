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

void print_env_variable(char *arg, t_data *data)
{
    int i = 1; // Start after the '$'
    char *var_name;
    char *var_value;

    if (arg[i] == '\0')
    {
        // No variable name after '$', print '$'
        ft_putchar_fd('$', 1);
        return;
    }

    if (arg[i] == '?')
    {
        // Variable is '?'
        var_name = ft_substr(arg, i, 1); // var_name = "?"
        i++; // Move index past '?'
    }
    else
    {
        // Parse variable name: letters, digits, underscores
        int start = i;
        while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
            i++;
        var_name = ft_substr(arg, start, i - start);
    }

    // Now expand the variable
    if (ft_strcmp(var_name, "?") == 0)
    {
        char *status_str = ft_itoa(data->state.last_exit_status);
        ft_putstr_fd(status_str, 1);
        free(status_str);
    }
    else
    {
        var_value = find_env_value(data->env, var_name);
        if (var_value)
            ft_putstr_fd(var_value, 1);
    }

    free(var_name);

    // Now print the rest of the argument
    if (arg[i] != '\0')
    {
        ft_putstr_fd(&arg[i], 1);
    }
}

/*
void	print_env_variable(char *arg, t_data *data)
{
	char	*env_type;
	char	*env_value;
	char	*status_str;


	if (arg[1] == '\0')
		ft_putchar_fd('$', 1);
   	else if (arg[1] == '?' && (arg[2] == '\0' || arg[2] == ' ')) // Ensure it's only $?
    {
        // Convert last exit status to string and output it
        char *status_str = ft_itoa(data->state.last_exit_status);
        ft_putstr_fd(status_str, 1);
        free(status_str);
    }
	else{
	env_type = &arg[1];
	env_value = find_env_value(data->env, env_type);
	if (env_value)
		ft_putstr_fd(env_value, 1);
	}
}
 */
void	print_quoted_arg(char *arg, t_data *data, char quote_type)
{
	int		j;
	int		k;
	char	*var_name;
	char	*env_value;
	char	*status_str;

	j = 0;
	while (arg[j])
	{
		if (quote_type == '"' && arg[j] == '$')
		{
			k = j + 1;
			if (arg[k] == '?')
			{
				status_str = ft_itoa(data->state.last_exit_status);
				ft_putstr_fd(status_str, 1);
				free(status_str);
				j = k + 1; // Move past '?'
			}
			else
			{
				while (arg[k] && (ft_isalnum(arg[k]) || arg[k] == '_'))
					k++;
				if (k > j + 1)
				{
					var_name = ft_substr(arg, j + 1, k - j - 1);
					env_value = find_env_value(data->env, var_name);
					if (env_value)
						ft_putstr_fd(env_value, 1);
					free(var_name);
					j = k;
				}
				else
				{
					ft_putchar_fd('$', 1);
					j++;
				}
			}
		}
		else
		{
			ft_putchar_fd(arg[j], 1);
			j++;
		}
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

void	process_argument(char *arg, t_data *data)
// probably because of this function the program thinks the first character in double quotes is a quote,
// so (echo "abcdefa") will print bcdef
{
	char quote_type;
	char *processed_arg;

	if (is_quote(arg[0]))
	{
		quote_type = arg[0];
		processed_arg = remove_balanced_quotes(arg);
		if (quote_type == '\'')
			print_escape(processed_arg);
		else if (quote_type == '\"')
		{
			processed_arg = remove_balanced_quotes(arg);
			print_quoted_arg(processed_arg, data, quote_type);
		}
		free(processed_arg);
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
