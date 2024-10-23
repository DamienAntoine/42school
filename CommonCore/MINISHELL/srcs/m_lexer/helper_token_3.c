#include "../../headers/minishell.h"

void	quote_check(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (c == '\"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
}

char	*remove_balanced_quotes(const char *input)
{
	char	*result;
	size_t	len;
	size_t	i;
	size_t	j;
	int		in_single_quotes;
	int		in_double_quotes;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	len = ft_strlen(input);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		quote_check(input[i], &in_single_quotes, &in_double_quotes);
		if ((input[i] == '\'' && !in_double_quotes) || (input[i] == '\"' && !in_single_quotes))
			i++;
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
