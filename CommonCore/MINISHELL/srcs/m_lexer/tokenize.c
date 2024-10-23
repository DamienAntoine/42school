#include "../../headers/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

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

void	process_quotes(const char *str, int *i, t_data *data)
{
	handle_single_quotes(str, i, data);
	handle_double_quotes(str, i, data);
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
	while (str[i])
	{
		process_quotes(str, &i, data);
		if (handle_variable_expansion(str, &i, &start, data))
			continue ;
		i++;
	}
	append_remaining_text(str, &i, &start, data);
	return (data->env->result);
}

int	quotes_check(const char *input)
{
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (input[i] == '\"')
			in_double_quotes = !in_double_quotes;
		if (input[i] == '$')
		{
			if (in_double_quotes)
				return (0);
			if (in_single_quotes)
				return (1);
		}
		i++;
	}
	return (0);
}

char	*remove_balanced_quotes(const char *input)
{
	char	*result;
	size_t	len;
	size_t	i;
	size_t	j;
	int		in_single_quotes;
	int		in_double_quotes;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	len = ft_strlen(input);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		if (input[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
		}
		else if (input[i] == '\"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

int	is_in_quotes(const char *arg, int position)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (i < position)
	{
		if (arg[i] == '\'')
			in_quotes++;
		i++;
	}
	return (in_quotes % 2 != 0);
}

char	*handle_quotes(const char *str, t_data *data)
{
	char	*expanded_str;
	char	*result;

	expanded_str = process_env_token(str, data);
	result = remove_balanced_quotes(expanded_str);
	free(expanded_str);
	return (result);
}

char	*ft_strtok(char *str, const char *delimiter)
{
	static char	*last;
	int			in_single_quotes;
	int			in_double_quotes;
	char		*start;

	in_single_quotes = 0;
	in_double_quotes = 0;
	if (str == NULL)
		str = last;
	if (str == NULL || *str == '\0')
		return (NULL);
	while (*str && ft_strchr(delimiter, *str))
		str++;
	if (*str == '\0')
		return (NULL);
	start = str;
	while (*str)
	{
		if (*str == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*str == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && !in_double_quotes)
		{
			if (ft_strchr("<>|", *str))
			{
				if (str != start)
				{
					last = str;
					return (ft_substr(start, 0, str - start));
				}
				if (*(str + 1) == *str)
					str++;
				last = str + 1;
				return (ft_substr(start, 0, str - start + 1));
			}
			if (ft_strchr(delimiter, *str))
				break ;
		}
		str++;
	}
	if (*str != '\0')
		*str++ = '\0';
	last = str;
	return (start);
}

char	**ft_tokenize(t_data *data, char *input)
{
	char			**args;
	char			*processed_input;
	char			*token;
	char			*expanded;
	int				i;
	t_token_list	*toklist;

	toklist = data->toklist;
	processed_input = trim_input(input);
	if (!processed_input)
		return (NULL);
	args = malloc(MAX_ARGS * sizeof(char *));
	if (!args)
	{
		free(input);
		return (NULL);
	}
	i = 0;
	token = ft_strtok(processed_input, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		args[i++] = ft_strdup(token);
		token = ft_strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	toklist->token_count = i;
	i = 0;
	while (args[i])
	{
		expanded = handle_quotes(args[i], data);
		free(args[i]);
		args[i] = expanded;
		i++;
	}
	free(processed_input);
	return (args);
}

char	*trim_input(char *input)
{
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, " \t\n\r");
	if (!trimmed_input || *trimmed_input == '\0')
	{
		free(trimmed_input);
		return (NULL);
	}
	return (trimmed_input);
}
