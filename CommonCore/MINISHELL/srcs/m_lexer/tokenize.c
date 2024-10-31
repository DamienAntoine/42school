#include "../../headers/minishell.h"

int	handle_exit_status_expansion(const char *str, int *i, int *start,
		t_data *data)
{
	char	*status_str;

	if (str[*start] == '?')
	{
		status_str = ft_itoa(data->state.last_exit_status);
		ft_strlcat(data->env->result, status_str, data->env->buffer_size);
		free(status_str);
		(*i)++;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
		{
			ft_strlcat_char(data->env->result, str[*i], data->env->buffer_size);
			(*i)++;
		}
		*start = *i;
		return (1);
	}
	return (0);
}

int	process_variable(const char *str, int *i, int *start, t_data *data)
{
	char	*temp;
	char	*expanded_var;

	if (!str[*start] || !(ft_isalnum(str[*start]) || str[*start] == '_'))
	{
		ft_strlcat(data->env->result, "$", data->env->buffer_size);
		*start = *i;
		return (1);
	}
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_' || str[*i] == '='
			|| str[*i] == ';'))
		(*i)++;
	temp = ft_substr(str, *start, *i - *start);
	if (temp && temp[0] != '\0')
	{
		expanded_var = expand_variable(temp, data);
		ft_strlcat(data->env->result, expanded_var, data->env->buffer_size);
		free(expanded_var);
	}
	free(temp);
	*start = *i;
	return (1);
}

int	handle_variable_expansion(const char *str, int *i, int *start, t_data *data)
{
	if (str[*i] == '$' && !data->env->in_single_quotes)
	{
		handle_unprocessed_string(str, i, start, data);
		(*i)++;
		*start = *i;
		if (handle_exit_status_expansion(str, i, start, data))
			return (1);
		return (process_variable(str, i, start, data));
	}
	return (0);
}

void	append_remaining_text(const char *str, int *i, int *start, t_data *data)
{
	char	*temp;

	if (*start < *i)
	{
		temp = ft_substr(str, *start, *i - *start);
		ft_strlcat(data->env->result, temp, data->env->buffer_size);
		free(temp);
	}
}

char	*process_env_token(const char *str, t_data *data)
{
	int	start;
	int	i;

	data->env->in_single_quotes = 0;
	data->env->in_double_quotes = 0;
	data->env->buffer_size = estimate_buffer_size(str, data);
	data->env->result = malloc(data->env->buffer_size);
	if (!data->env->result)
		return (NULL);
	data->env->result[0] = '\0';
	i = 0;
	start = 0;
	while (str[i] != '\0')
	{
		process_quotes(str, &i, data);
		if (handle_variable_expansion(str, &i, &start, data))
			continue ;
		if (str[i] != '\0')
			i++;
	}
	append_remaining_text(str, &i, &start, data);
	return (data->env->result);
}
