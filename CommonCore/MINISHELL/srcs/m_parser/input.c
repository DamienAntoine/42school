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
    size_t total_len = 0;
    int unbalanced_quotes;

    // Initial prompt
    input = readline("\033[35mMSL> \033[0m");

    if (input == NULL) // Handle Ctrl+D
        return NULL;

    total_len = ft_strlen(input);
    full_input = ft_strdup(input); // Duplicate input for further processing
    free(input);

    // Check for unbalanced quotes and continue prompting if necessary
    unbalanced_quotes = !are_quotes_balanced(full_input);
    while (unbalanced_quotes)
    {
        input = readline("> "); // Secondary prompt for continued input

        if (input == NULL) // Handle Ctrl+D
        {
            free(full_input);
            return NULL;
        }

        // Reallocate space for concatenating newline and input
        total_len += ft_strlen(input) + 1; // +1 for newline
        full_input = realloc(full_input, total_len + 1); // +1 for null-terminator

        if (!full_input)
        {
            free(input);
            return NULL; // Handle allocation failure
        }

        // Concatenate newline and the new input
        ft_strlcat(full_input, "\n", total_len + 1);
        ft_strlcat(full_input, input, total_len + 1);

        free(input);

        unbalanced_quotes = !are_quotes_balanced(full_input);
    }

    // Remove balanced quotes before returning the full input
    char *final_input = remove_balanced_quotes(full_input);  // Remove outer balanced quotes
    free(full_input);

    return final_input;
}

/* char *get_full_input(void)
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
 
    // Remove balanced quotes before returning the full input
    temp = full_input;
    full_input = remove_balanced_quotes(full_input);  // Remove outer balanced quotes
    free(temp);

 
	return (full_input);
} */
