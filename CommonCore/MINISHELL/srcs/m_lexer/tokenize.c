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
	start = str;
	end = start + ft_toklen(start, delimiter);
	if (*end != '\0')
	{
		*end = '\0';
		last = end + 1; // set the last pointer to the start of the next token
	}
	else
		last = NULL;
	return (start);
}

//lexer takes the whole command line and splits every word into a token to store them into token_list->tokens.
//example : ls -l = token 1 is "ls", token 2 is "-l"
char	**ft_tokenize(char *input)
{
	char	**args;
	int		i;
	char	*token;

	args = malloc(MAX_ARGS * sizeof(char *));
	i = 0;
	token = ft_strtok(input, " \t\n|<>");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = ft_strtok(NULL, " \t\n|<>");
	}
	args[i] = NULL;
	return (args);
}
