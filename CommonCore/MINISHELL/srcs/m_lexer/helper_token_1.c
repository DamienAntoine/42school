#include "../../headers/minishell.h"

char	*expand_variable(const char *var_name, t_data *data)
{
	char	*value;

	if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup(""));
	value = find_env_value(data->env, var_name);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

size_t	estimate_buffer_size(const char *str, t_data *data)
{
	size_t	size;
	int		i;
	int		start;
	char	*var_name;
	char	*expanded_var;

	size = ft_strlen(str) + 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				size += 11;
				i++;
			}
			else
			{
				start = i;
				while (str[i] && (isalnum(str[i]) || str[i] == '_'))
					i++;
				var_name = ft_substr(str, start, i - start);
				expanded_var = expand_variable(var_name, data);
				size += ft_strlen(expanded_var);
				free(var_name);
				free(expanded_var);
			}
		}
		else
			i++;
	}
	return (size);
}

void	handle_single_quotes(const char *str, int *i, t_data *data)
{
	if (str[*i] == '\'' && !data->env->in_double_quotes)
	{
		data->env->in_single_quotes = !data->env->in_single_quotes;
		(*i)++;
	}
}

void	handle_double_quotes(const char *str, int *i, t_data *data)
{
	if (str[*i] == '\"')
	{
		data->env->in_double_quotes = !data->env->in_double_quotes;
		(*i)++;
	}
}

void	handle_unprocessed_string(const char *str, int *i, int *start,
		t_data *data)
{
	char	*temp;

	if (*i > *start)
	{
		temp = ft_substr(str, *start, *i - *start);
		ft_strlcat(data->env->result, temp, data->env->buffer_size);
		free(temp);
	}
}
