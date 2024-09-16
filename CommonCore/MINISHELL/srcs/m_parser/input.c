#include "../../headers/minishell.h"

int	are_quotes_balanced(const char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && double_quote % 2 == 0)
			single_quote++;
		else if (*input == '\"' && single_quote % 2 == 0)
			double_quote++;
		input++;
	}
	return (single_quote % 2 == 0 && double_quote % 2 == 0);
}

char *get_full_input(void)
{
	char *input;
	char *full_input;
	char *temp;
	int unbalanced_quotes;

	full_input = NULL;
	// Initial prompt
	input = readline("\033[35mMSL> \033[0m");

	if (input == NULL) // Handle Ctrl+D
	{
		if (full_input)
			free(full_input);
		return (NULL);
	}


	full_input = ft_strdup(input); // Duplicate input for further processing
	free(input);

	// Check for unbalanced quotes and continue prompting if necessary
	unbalanced_quotes = !are_quotes_balanced(full_input);
	while (unbalanced_quotes)
	{
		temp = full_input;
		input = readline("> "); // Secondary prompt for continued input
		if (input == NULL) // Handle Ctrl+D
		{
			free(temp);
			return (NULL);
		}
		full_input = ft_strjoin(full_input, "\n");
		full_input = ft_strjoin(full_input, input); // Join input lines
		free(temp);
		free(input);

		unbalanced_quotes = !are_quotes_balanced(full_input);
	}
	return (full_input);
}
