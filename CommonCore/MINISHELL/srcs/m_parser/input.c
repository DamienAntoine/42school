#include "../../headers/minishell.h"

int	are_quotes_balanced(const char *input)
{
	int	i;
	int	first_quote;

	i = 0;
	first_quote = 0;
	while (input[i])
	{
		if (first_quote == 0)
		{
			if (input[i] == '\'' && (input[i - 1] != '\\'))
				first_quote = 1;
			else if (input[i] == '\"' && (input[i - 1] != '\\'))
				first_quote = 2;
		}
		else if (first_quote == 1)
		{
			if (input[i] == '\'' && (input[i - 1] != '\\'))
				first_quote = 0;
		}
		else if (first_quote == 2)
		{
			if (input[i] == '\"' && (input[i - 1] != '\\'))
				first_quote = 0;
		}
		i++;
	}
	return (first_quote == 0);
}

char	*get_full_input(void)
{
	char	*input;
	char	*full_input;
	char	*temp;
	int		unbalanced_quotes;

	full_input = NULL;
	input = readline("\033[35mMSL> \033[0m");
	if (input == NULL)
		return (NULL);
	full_input = ft_strdup(input);
	free(input);
	unbalanced_quotes = !are_quotes_balanced(full_input);
	while (unbalanced_quotes)
	{
		input = readline("\033[35m> \033[0m");
		if (input == NULL)
		{
			free(full_input);
			return (NULL);
		}
		temp = full_input;
		full_input = ft_strjoin(temp, "\n");
		free(temp);
		temp = full_input;
		full_input = ft_strjoin(temp, input);
		free(temp);
		free(input);
		unbalanced_quotes = !are_quotes_balanced(full_input);
	}
	return (full_input);
}
