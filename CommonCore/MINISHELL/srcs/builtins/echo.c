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

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*expand_variable(const char *var_name, t_data *data)
{
	char	*value;

	if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup(""));
	value = find_env_value(data->env, var_name);
	printf("env value %s\nenv name %s\n", value, var_name);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

char	*process_double_quotes(const char *str, t_data *data)
{
	char	*result;
	char	*temp;
	int		start;
	int		i;
	char	*expanded_var;
	char	*status_str;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	temp = NULL;
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')//echo 123$PWD: i=3
		{
			if (i > start)//put everything before $ in temp
			{
				temp = ft_substr(str, start, i - start);
				ft_strcat(result, temp);
				free(temp);
			}

			i++;//skip $
			start = i;//start = first char after $
			printf("i - start : %d\n", i - start);
			printf("i : %d\n", i);
			printf("start : %d\n", start);
			if (str[start] == '?' && (!str[start + 1] || !isalnum(str[start + 1])) )
			{
				status_str = ft_itoa(data->state.last_exit_status);
				ft_strcat(result, status_str);
				free(status_str);
				i += 2;
				start = i;
				continue ;
			}
			while (str[i] && (isalnum(str[i]) || str[i] == '_'))
            	i++;
            temp = ft_substr(str, start, i);//extract env var name into temp
			printf("temp content: %s\n", temp);

            if (temp && temp[0] != '\0')
            {
                expanded_var = expand_variable(temp, data);
				printf("%s\n", expanded_var);
                ft_strcat(result, expanded_var);
                free(expanded_var);
            }
			printf("crash1: %s, %p\n", temp, temp);
            free(temp);
			printf("crash2\n");
            start = i;
        }
        i++;
    }
	if (start < i)
	{
		temp = ft_substr(str, start, i - start);
		ft_strcat(result, temp);
		free(temp);
	}
	return (result);
}


int	is_in_single_quote(const char *arg, int position)
{
	int	i;
	int	single_quotes;

	i = 0;
	single_quotes = 0;
	while (i < position)
	{
		if (arg[i] == '\'')
			single_quotes++;
		i++;
	}
	return (single_quotes % 2 != 0);
}

void	process_argument(char *arg, t_data *data)
{
	char	*processed_arg;
	char	*temp;
	char	*quote_buffer;
	int		i;
	int		start;
	char	quote_type;
	char	*expanded_content;

	ft_putstr_fd("test\n", 1);
	processed_arg = malloc(ft_strlen(arg) + 1);
	if (!processed_arg)
		return ;
	processed_arg[0] = '\0';
	quote_buffer = NULL;
	i = 0;
	start = 0;
	while (arg[i])
	{
		if (is_quote(arg[i]))
		{
			quote_type = arg[i];
			if (i > start)
			{
				temp = ft_substr(arg, start, i - start);
				if (quote_type == '\'')
					ft_strcat(processed_arg, temp);
				else
				{
					expanded_content = process_double_quotes(temp, data);
					ft_strcat(processed_arg, expanded_content);
					free(expanded_content);
				}
				free(temp);
			}
			i++;
			start = i;
			quote_buffer = malloc(ft_strlen(arg) + 1);
			if (!quote_buffer)
			{
				free(processed_arg);
				return ;
			}
			quote_buffer[0] = '\0';
			while (arg[i] && arg[i] != quote_type)
			{
				temp = ft_substr(arg, i, 1);
				ft_strcat(quote_buffer, temp);
				free(temp);
				i++;
			}
			if (quote_type == '\'')
				ft_strcat(processed_arg, quote_buffer);
			else if (quote_type == '\"')
			{
				expanded_content = process_double_quotes(quote_buffer, data);
				ft_strcat(processed_arg, expanded_content);
				free(expanded_content);
			}
			free(quote_buffer);
			start = ++i;
		}
		else
			i++;
	}
	temp = ft_substr(arg, start, i - start);
	if (is_in_single_quote(arg, start))
		ft_strcat(processed_arg, temp);
	else
	{
		printf("temp before process: '%s'\n", temp);
		expanded_content = process_double_quotes(temp, data);
		ft_strcat(processed_arg, expanded_content);
		free(expanded_content);
	}
	free(temp);

	print_escape(processed_arg);
	free(processed_arg);
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
