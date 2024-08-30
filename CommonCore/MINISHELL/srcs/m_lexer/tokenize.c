#include "../../headers/minishell.h"

size_t ft_toklen(const char *str, const char *delim)
{
	size_t len = 0;
	int i;

	if (str == NULL || delim == NULL)
		return 0;
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

// strtok is like ft_split but it replaces delimiter characters with null characters,making every word of the string a token. It returns the next token everytime its called
char	*ft_strtok(char *str, const char *delimiter)
{
	static char *last; // keeps track of next token
	char	*start;
	char	*end;

	if (str == NULL)
		str = last;
	if (str == NULL || *str == '\0')
		return (NULL);

	while (*str && ft_strchr(delimiter, *str))
		str++;
	if (*str == '\0')
	{
		last = NULL;
		return NULL;
	}


	start = str;
	end = start + ft_toklen(start, delimiter);
	if (*end != '\0')
	{
		*end = '\0';
        /*while (is_delimiter(*end + 1, delimiter))
            end++;*/
		last = end + 1; // set the last pointer to the start of the next token
	}
	else
		last = NULL;
	return (start);
}

//lexer takes the whole command line and splits every word into a token to store them into token_list->tokens.
//example : ls -l = token 1 is "ls", token 2 is "-l"
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
	token = ft_strtok(input, " \t\n|<>");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = ft_strdup(token);
		token = ft_strtok(NULL, " \t\n|<>");
	}
	toklist->token_count = i;
	args[i] = NULL;
	free(input);
	return (args);
}

char	*trim_input(char *input)
{
	char *trimmed_input = ft_strtrim(input, " \t\n\r");

    if (trimmed_input == NULL || *trimmed_input == '\0')
	{
		free(trimmed_input);
		return (NULL);
	}
	return (trimmed_input);
}

int is_delimiter(char c, const char *delimiter)
{
    int i;

    i = 0;
    while (delimiter[i])
    {
        if (delimiter[i] == c)
            return (1);
        i++;
    }
    return (0);
}
