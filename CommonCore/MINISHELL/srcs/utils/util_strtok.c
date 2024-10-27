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
	if (str != start)
	{
		*last = str;
		return (ft_substr(start, 0, str - start));
	}
	if (*(str + 1) == *str)
		str++;
	*last = str + 1;
	return (ft_substr(start, 0, str - start + 1));
}

void	toggle_quotes(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
	else if (c == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
}

char	*ft_strtok(char *str, const char *delimiter)
{
	static char	*last;
	int			in_single_quotes;
	int			in_double_quotes;
	char		*start;

	in_single_quotes = 0;
	in_double_quotes = 0;
	str = initialize_str(str, delimiter, &last);
	if (!str)
		return (NULL);
	start = str;
	while (*str)
	{
		toggle_quotes(*str, &in_single_quotes, &in_double_quotes);
		if (!in_single_quotes && !in_double_quotes)
		{
			if (ft_strchr("<>|", *str))
				return (check_special_characters(str, start, &last));
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
