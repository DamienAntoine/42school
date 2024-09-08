#include "../../headers/minishell.h"

// Function to check if the quotes are balanced
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

// Function to handle input and ensure quotes are closed
char *get_full_input(void)
{
	char *input;
	char *full_input = NULL;
	char *temp;
	int unbalanced_quotes;

	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL) // Handle Ctrl+D
		{
			if (full_input)
				free(full_input);
			return (NULL);
		}

		if (full_input == NULL)
			full_input = ft_strdup(input);
		else
		{
			temp = full_input;
			full_input = ft_strjoin(full_input, input);
			free(temp);
		}
		free(input);

		unbalanced_quotes = !are_quotes_balanced(full_input);
		if (!unbalanced_quotes)
			break;

		write(1, "> ", 2);
	}
	return (full_input);
}