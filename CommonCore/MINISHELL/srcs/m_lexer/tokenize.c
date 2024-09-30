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
			if (str[i] == '?') // for $? exit status
			{
				size += 11;
				// maximum size of an int converted to string (plus sign and null byte)
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

char	*process_env_token(const char *str, t_data *data)
{
	char	*result;
	char	*temp;
	int		start;
	int		i;
	char	*expanded_var;
	char	*status_str;
	size_t	buffer_size;
	int		in_single_quotes;
	int		in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	buffer_size = estimate_buffer_size(str, data);
	result = malloc(buffer_size);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	start = 0;
	while (str[i])
	{
		// Toggle single quotes
		if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
			continue ;
		}
		// Toggle double quotes
		if (str[i] == '\"')
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue ;
		}

		if (str[i] == '$')
		{
			// expand variables outside single quotes
			if (in_single_quotes && !in_double_quotes)
			{
				ft_strlcat(result, "$", buffer_size);
				i++;
				start = i;
				continue;
			}
            

            /*
            if (!str[start] || !(isalnum(str[start]) || str[start] == '_'))//print $ if not followed by anything
			{
				ft_strlcat(result, "$", buffer_size);
				start = i;
				continue ;
			}
            else if (str[start] == '?' && isalnum(str[start + 1])) // handle $?HELLO)
			{
				status_str = ft_itoa(data->state.last_exit_status);
				ft_strlcat(result, status_str, buffer_size);
				free(status_str);
				i++;
				// append characters after $?
				while (isalnum(str[i]) || str[i] == '_')
				{
					ft_strlcat_char(result, str[i], buffer_size);
					i++;
				}
				start = i;
				continue;
			}*/

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
				continue ;
			}

			// Expand environment variables
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '=' || str[i] == ';'))
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
		else
			i++;
	}
	if (start < i)
	{
		temp = ft_substr(str, start, i - start);
		ft_strlcat(result, temp, buffer_size);
		free(temp);
	}
	return (result);
}


int quotes_check(const char *input)
{
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (input[i])
	{
		// toggle single quotes only if not in double quotes
		if (input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		// toggle double quotes
		else if (input[i] == '\"')
			in_double_quotes = !in_double_quotes;

		if (input[i] == '$')
		{
			// double quotes: expand
			if (in_double_quotes)
				return (0);
			// single quotes: do not expand
			if (in_single_quotes)
				return (1);
		}
		i++;
	}
	return (0); // Return 0 if no '$' is found in single quotes
}


#include <stdlib.h>
#include <string.h>

char *remove_balanced_quotes(const char *input) {
    char *result;
    size_t len;
    size_t i = 0;
    size_t j = 0;
    char outer_quote = 0;
    size_t closing_quote = 0;

    len = ft_strlen(input);

    // Find outer quotes
    while (input[i]) {
        if (outer_quote == 0 && (input[i] == '\"' || input[i] == '\'')) {
            outer_quote = input[i];
            closing_quote = i + 1;

            // Find the closing quote
            while (input[closing_quote]) {
                if (input[closing_quote] == outer_quote) {
                    break;
                }
                closing_quote++;
            }
            // If a matching closing quote is found
            if (input[closing_quote] == outer_quote) {
                break; // Exit outer loop if we find the closing quote
            }
        }
        i++;
    }

    // Adjust length if outer quotes are present
    if (outer_quote && input[len - 1] == outer_quote) {
        len -= 2; // Exclude the outer quotes
    }

    // Allocate memory for the result
    result = malloc(len + 1);
    if (!result) {
        return NULL; // Handle allocation failure
    }

    // Set the start index to skip the outer quote if it exists
    size_t start_index = (outer_quote) ? 1 : 0;
    size_t end_index = (outer_quote) ? closing_quote : len;

    // Copy the characters excluding the outer quotes
    while (start_index < end_index) {
        result[j++] = input[start_index];
        start_index++;
    }

    result[j] = '\0'; // Null-terminate the result string
    return result;
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

char *handle_quotes(const char *str, t_data *data)
{
	char	*expanded_str;
    char    *result;
    int     i;
	size_t	len;

    expanded_str = process_env_token(str, data);
    len = ft_strlen(expanded_str);
    i = 0;
    result = remove_balanced_quotes(expanded_str);
	return (result);
}

char	*ft_strtok(char *str, const char *delimiter)
{
	static char	*last;
	int			in_single_quotes;
	int			in_double_quotes;
	char		*end;
	char		*start;

	in_double_quotes = 0;
	in_single_quotes = 0;
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
		else if (ft_strchr(delimiter, *str) && !in_double_quotes
			&& !in_single_quotes)
			break ;
		str++;
	}
	end = str;
	if (*end != '\0')
		*end++ = '\0';
	last = end;
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
	toklist->token_count = i; // update tokencount
	// handle quotes and variable expansion
	i = 0;
	while (args[i])
	{
		expanded = handle_quotes(args[i], data);// find expanded value and remove the quotes
		free(args[i]);
		args[i] = expanded;// assign the expanded string to args[i]
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
