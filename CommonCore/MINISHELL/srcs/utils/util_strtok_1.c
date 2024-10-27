#include "../../headers/minishell.h"

char	*parse_token(char *str, const char *delimiter, char **last)
{
	int		in_single_quotes;
	int		in_double_quotes;
	char	*start;

	in_single_quotes = 0;
	in_double_quotes = 0;
	start = str;
	while (*str)
	{
		toggle_quotes(*str, &in_single_quotes, &in_double_quotes);
		if (!in_single_quotes && !in_double_quotes)
		{
			if (ft_strchr("<>|", *str))
				return (check_special_characters(str, start, last));
			if (ft_strchr(delimiter, *str))
				break ;
		}
		str++;
	}
	if (*str != '\0')
		*str++ = '\0';
	*last = str;
	return (start);
}

char	*ft_strtok(char *str, const char *delimiter)
{
	static char	*last;

	str = initialize_tokenizer(str, delimiter, &last);
	if (!str)
		return (NULL);
	return (parse_token(str, delimiter, &last));
}
