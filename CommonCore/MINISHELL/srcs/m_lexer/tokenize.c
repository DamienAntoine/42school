#include "../../headers/minishell.h"

size_t	ft_toklen(const char *str, const char *delim)
{
	size_t	len;
	int		i;

	len = 0;
	if (str == NULL || delim == NULL)
		return (0);
	while (str[len])
	{
		i = 0;
		while (delim[i])
		{
			if (str[len] == delim[i])
				return (len);
			i++;
		}
		len++;
	}
	return (len);
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
	// Remove surrounding double quotes if the token was quoted
	if ((*start == '"' && *(end - 1) == '"') || (*start == '\'' && *(end
			- 1) == '\''))
	{
		start++;
		*(end - 1) = '\0'; // Null-terminate after removing the closing quote
	}
	return (start);
}

// lexer takes the whole command line and splits every word into a token to store them into token_list->tokens.
// example : ls -l = token 1 is "ls", token 2 is "-l"
char	**ft_tokenize(t_token_list *toklist, char *input)
{
	char	**args;
	int		i;
	char	*token;

	input = trim_input(input);
	if (input == NULL || *input == '\0')
	{
		free(input);
		toklist->token_count = 0;
		return (NULL);
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
