#include "../../headers/minishell.h"

//here expand env variables if they are not inside singlequotes
//handle $ and $?
//handle quotes
//so echo only prints every arguments it gets literally and doesnt do any more checks, and we can use the expanded variabled in other things easier too

int    handle_quotes(const char *str, t_data *data)
{
    int i;

    i = 0;
    if (are_quotes_balanced(str) == 2)//balanced double quotes
    {
        remove_balanced_quotes(str);
        return (0);
    }
    if (are_quotes_balanced(str) == 1)//balanced single quotes
        return (1);
    return (0);
}

char	*process_tokens(const char *str, t_data *data)
{
	char	*result;
	char	*temp;
	int		start;
	int		i;
	char	*expanded_var;
	char	*status_str;
	size_t	buffer_size;

	// calculate buffer size to avoid realloc function
	buffer_size = estimate_buffer_size(str, data);
	result = malloc(buffer_size);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i > start) // put everything thats before $ inside result string
			{
				temp = ft_substr(str, start, i - start);
				ft_strlcat(result, temp, buffer_size);
				free(temp);
			}
			i++; // skip '$'
			start = i;


			// handle $?
			if (str[start] == '?' && (!str[start + 1] || !isalnum(str[start + 1])))
			{
				status_str = ft_itoa(data->state.last_exit_status);
				ft_strlcat(result, status_str, buffer_size);
				free(status_str);
				i++;
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
			}


			if (!str[start] || !(isalnum(str[start]) || str[start] == '_'))//print $ if not followed by anything
			{
				ft_strlcat(result, "$", buffer_size);
				start = i;
				continue ;
			}

			// env variables
			while (str[i] && (isalnum(str[i]) || str[i] == '_' || str[i] == '=' || str[i] == ':'))
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
	if (start < i) // append remaining part after the last '$'
	{
		temp = ft_substr(str, start, i - start);
		ft_strlcat(result, temp, buffer_size);
		free(temp);
	}
	return (result);
}

char	*ft_strtok(char *str, const char *delimiter)
{
	char	*start;
	char	*end;
	int		in_double_quotes;
	int		in_single_quotes;

	static char *last;

	in_double_quotes = 0;
	in_single_quotes = 0;
	if (str == NULL)
		str = last;
	if (str == NULL || *str == '\0')
		return (NULL);
	// Skip leading delimiters
	while (*str && ft_strchr(delimiter, *str))
		str++;
	if (*str == '\0')
	{
		last = NULL;
		return (NULL);
	}
	start = str;
	while (*str)
	{
		if (*str == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
				// Toggle in_double_quotes when encountering a double quote
		else if (*str == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
				// Toggle in_single_quotes when encountering a single quote
		else if (ft_strchr(delimiter, *str) && !in_double_quotes
			&& !in_single_quotes)
			break ;
		str++;
	}
	end = str; // End points to the current position of str
	if (*end != '\0')
	{
		*end = '\0';    // Null-terminate the current token
		last = end + 1; // Set the last pointer to the start of the next token
	}
	else
		last = NULL;
	return (start);
}

// lexer takes the whole command line and splits every word into a token to store them into token_list->tokens.
// example : ls -l = token 1 is "ls", token 2 is "-l"
char	**ft_tokenize(t_data *data, char *input)
{
    int		        i;
    char            *processed_input;
	char	        **args;
	char	        *token;
    t_token_list    *toklist;

    toklist = data->toklist;
    processed_input = malloc(ft_strlen(input) + 1);
    if (!processed_input)
        return (NULL);
	processed_input = trim_input(input);
    if (process_quotes(input, data) == 1)//balanced single quotes, dont expand
    {
        i = 0;
        while (input[i])
        {
            if (input[i] == '\'' && are_quotes_balanced(input == 1))
                i++;
            
        }
    }
    else//balanced double quotes found and removed, expand env
    {
        processed_input = process_tokens(processed_input, data);
	    if (processed_input == NULL || *processed_input == '\0')
        {
            free(input);
            toklist->token_count = 0;
            return (NULL);
        }
    }
	args = malloc(MAX_ARGS * sizeof(char *));
	if (!args)
	{
		free(input);
		return (NULL);
	}
	i = 0;
	token = ft_strtok(input, " \t\n");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = ft_strdup(token);
		token = ft_strtok(NULL, " \t\n");
	}
	toklist->token_count = i;
	args[i] = NULL;
	free(input);
	return (args);
}

char	*trim_input(char *input)
{
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, " \t\n\r");
	if (trimmed_input == NULL || *trimmed_input == '\0')
	{
		free(trimmed_input);
		return (NULL);
	}
	return (trimmed_input);
}
