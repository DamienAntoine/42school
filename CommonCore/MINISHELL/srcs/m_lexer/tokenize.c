#include "../../headers/minishell.h"

// Expand environment variables if they are not inside single quotes
// Handle $ and $? expansions inside double quotes
// This version only prints arguments literally in echo, allowing the expanded variables to be used elsewhere

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

char *expand_variable(const char *var_name, t_data *data)
{
	char	*value;

	printf("Trying to expand variable: %s\n", var_name); // Debug print
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup(""));

	value = find_env_value(data->env, var_name);
	if (value)
	{
		printf("Found value: %s\n", value); // Debug print
		return (ft_strdup(value));
	}
	else
	{
		printf("Variable not found in environment\n"); // Debug print
		return (ft_strdup(""));
	}
}


char	*process_env_token(const char *str, t_data *data, int in_single_quotes)
{
	char	*result;
	char	*temp;
	int		start;
	int		i;
	char	*expanded_var;
	char	*status_str;
	size_t	buffer_size;

	// Calculate buffer size to avoid realloc
	buffer_size = estimate_buffer_size(str, data);
	result = malloc(buffer_size);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$' && in_single_quotes == 0) // Skip expansion if inside single quotes
		{
			if (i > start)
			{
				temp = ft_substr(str, start, i - start);
				ft_strlcat(result, temp, buffer_size);
				free(temp);
			}
			i++;
			start = i;

			// Handle $?
			if (str[start] == '?' && (!str[start + 1] || !isalnum(str[start + 1])))
			{
				status_str = ft_itoa(data->state.last_exit_status);
				ft_strlcat(result, status_str, buffer_size);
				free(status_str);
				i++;
				start = i;
				continue;
			}

			// Env variables
			while (str[i] && (isalnum(str[i]) || str[i] == '_'))
				i++;
			temp = ft_substr(str, start, i - start);
			if (temp && temp[0] != '\0')
			{
				expanded_var = expand_variable(temp, data);
				ft_strlcat(result, expanded_var, buffer_size);
				free(expanded_var);
			}
			free(temp);
			start = i;
		}
		i++;
	}
	if (start < i)
	{
		temp = ft_substr(str, start, i - start);
		ft_strlcat(result, temp, buffer_size);
		free(temp);
	}
	return result;
}


char *handle_quotes(const char *str, t_data *data)
{
	char *expanded_str;

	if (are_quotes_balanced(str) == 2) // double quotes
		expanded_str = process_env_token(str, data, 0);
	else if (are_quotes_balanced(str) == 1) // single quotes, no expansion
		expanded_str = process_env_token(str, data, 1);
	else
		expanded_str = ft_strdup(str); // return original string

	return (expanded_str);
}

char	*ft_strtok(char *str, const char *delimiter)
{
	static char *last;
	char *start, *end;
	int	in_double_quotes = 0, in_single_quotes = 0;

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
		else if (ft_strchr(delimiter, *str) && !in_double_quotes && !in_single_quotes)
			break;
		str++;
	}
	end = str;
	if (*end != '\0')
		*end++ = '\0';
	last = end;
	return (start);
}

char **ft_tokenize(t_data *data, char *input)
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
	toklist->token_count = i;//update tokencount

	// handle quotes and variable expansion
	i = 0;
	while (args[i])
	{
		printf("arg before handlequote: %s\n", args[i]);
		expanded = handle_quotes(args[i], data); // replace with expanded value (it finds the value but doesnt replace the token)

		free(args[i]); // free old string
		args[i] = expanded; // assign the expanded string to args[i] (not working ?)

		printf("arg after handlequote: %s\n", args[i]);
		i++;
	}
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
