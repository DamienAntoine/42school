#include "../../headers/minishell.h"

/* 

// Helper function to remove only outer balanced quotes and preserve inner content (newlines, etc.)
char *remove_balanced_quotes(const char *input)
{
    int len = strlen(input);

    // If the string is too short to have balanced quotes, return it as-is
    if (len < 2)
        return strdup(input);

//    int single_quote = 0, double_quote = 0;
    int i = 0, j = 0;
    
    char *result = malloc(len + 1); // Allocate memory for the result string

    // Check if the first and last characters are matching quotes
    if ((input[0] == '\'' && input[len - 1] == '\'') || (input[0] == '\"' && input[len - 1] == '\"'))
    {
        // Skip the outermost quotes and copy the rest
        i = 1;  // Skip the first quote
        len--;  // Skip the last quote
    }

    // Loop through the string, copying characters and handling quotes inside the string
    while (i < len)
    {
        result[j++] = input[i]; // Copy all characters inside quotes (including newlines)
        i++;
    }

    result[j] = '\0'; // Null-terminate the result string
    return result;
}
*/

// Helper function to remove balanced quotes from a string
char *remove_balanced_quotes(const char *input)
{
    int len = ft_strlen(input);
    char *result = malloc(len + 1);  // Allocate memory for the result
    if (!result)
        return NULL;  // Memory allocation failure

    int i = 0;
	int j = 0;
    int single_quote = 0;
	int double_quote = 0;

    while (input[i])
    {
        // Toggle quotes if unbalanced
        if (input[i] == '\'' && double_quote % 2 == 0)
        {
            single_quote++;
        }
        else if (input[i] == '\"' && single_quote % 2 == 0)
        {
            double_quote++;
        }
        else
        {
            result[j++] = input[i];  // Copy the character if it's not a part of balanced quotes
        }
        i++;
    }

    result[j] = '\0';  // Null-terminate the result string
    return result;
}  


int	are_quotes_balanced(const char *input)
{
	int	i;

	i = 0;
	int first_quote = 0; // 1 for single quote, 2 for double quote
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
<<<<<<< HEAD
 
    // Remove balanced quotes before returning the full input
    temp = full_input;
    full_input = remove_balanced_quotes(full_input);  // Remove outer balanced quotes
    free(temp);

 
	return (full_input);
} */
=======
	full_input = remove_balanced_quotes(full_input);
	return (full_input);
}

char	*remove_balanced_quotes(const char *input)
{
	int	len;
	int	i;
	int	j;
	int	single_quote;
	int	double_quote;

	len = ft_strlen(input);
	char *result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && double_quote % 2 == 0)
			single_quote++;
		else if (input[i] == '\"' && single_quote % 2 == 0)
			double_quote++;
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
>>>>>>> fb18306241e283602bca2004688fde48863ab953
