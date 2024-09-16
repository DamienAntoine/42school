#include "../../headers/minishell.h"

int	are_quotes_balanced(const char *input)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && (i == 0 || input[i - 1] != '\\'))
			single_quotes = !single_quotes;
		else if (input[i] == '\"' && (i == 0 || input[i - 1] != '\\'))
			double_quotes = !double_quotes;
		i++;
	}
	return (single_quotes == 0 && double_quotes == 0);// return 1 if quotes are balanced
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
		input = readline("> ");
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
