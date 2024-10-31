#include "../../headers/minishell.h"

char	*initialize_str(char *str, const char *delimiter, char **last)
{
	if (str == NULL)
		str = *last;
	if (str == NULL || *str == '\0')
		return (NULL);
	while (*str && ft_strchr(delimiter, *str))
		str++;
	if (*str == '\0')
		return (NULL);
	*last = str;
	return (str);
}

char	*check_special_characters(char *str, char *start, char **last)
{
    char *result;

    if (str != start)
    {
        *last = str;
        result = ft_substr(start, 0, str - start);
        return (result);
    }
    if (*(str + 1) == *str)
        str++;
    *last = str + 1;
    result = ft_substr(start, 0, str - start + 1);
    return (result);
}

void	toggle_quotes(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
	else if (c == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
}

char	*process_token_character(char *str, char *start, const char *delimiter,
		char **last)
{
	if (ft_strchr("<>|", *str))
		return (check_special_characters(str, start, last));
	if (ft_strchr(delimiter, *str))
	{
		*str = '\0';
		*last = str + 1;
		return (ft_substr(start, 0, str - start));
	}
	return (NULL);
}

char	*initialize_tokenizer(char *str, const char *delimiter, char **last)
{
	str = initialize_str(str, delimiter, last);
	return (str);
}
