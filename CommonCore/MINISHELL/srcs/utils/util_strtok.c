#include "../../headers/minishell.h"




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
