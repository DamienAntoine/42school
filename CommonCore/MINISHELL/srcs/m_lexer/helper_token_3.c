#include "../../headers/minishell.h"

void	quote_check(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (c == '\"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
}
void	process_input(const char *input, char *result, size_t len, int *in_single_quotes, int *in_double_quotes)
{
	size_t	i = 0;
	size_t	j = 0;

	while (i < len)
	{
		quote_check(input[i], in_single_quotes, in_double_quotes);
		if ((input[i] == '\'' && !(*in_double_quotes)) || (input[i] == '\"' && !(*in_single_quotes)))
			i++;
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
}

char	*remove_balanced_quotes(const char *input)
{
	char	*result;
	size_t	len;
	int		in_single_quotes = 0;
	int		in_double_quotes = 0;

	len = ft_strlen(input);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	process_input(input, result, len, &in_single_quotes, &in_double_quotes);

	return (result);
}
