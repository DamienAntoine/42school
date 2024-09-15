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

/*

char *get_full_input(void)
{
    char *input;
    char *full_input = NULL;
    char *temp;
    int unbalanced_quotes;

    while (1)
    {
        // Show prompt
        write(1, "\033[35mMSL> \033[0m", 14);

        input = readline(""); // Using readline for handling arrow keys and history

        if (input == NULL) // Handle Ctrl+D
        {
            if (full_input)
                free(full_input);
            return (NULL);
        }

        if (full_input == NULL)
        {
            full_input = ft_strdup(input);
        }
        else
        {
            temp = full_input;
            full_input = ft_strjoin(full_input, input);
            free(temp);
        }
        free(input);

        // Check for unbalanced quotes
        unbalanced_quotes = !are_quotes_balanced(full_input);
        if (!unbalanced_quotes)
            break;

        // If quotes are unbalanced, display continuation prompt '>'
        write(1, "> ", 2);
    }

    return (full_input);
}
*/

/*
char *get_full_input(void)
{
    struct termios orig_termios;
    enable_raw_mode(&orig_termios);

    char *full_input = NULL;
    char *temp;
    int unbalanced_quotes;
    char c;
    int pos = 0;
 

    full_input = (char *)malloc(buf_size);
    if (!full_input)
        return NULL;

    // Write prompt first (MSL>)
    write(STDOUT_FILENO, "\033[35mMSL> \033[0m", 14);

    while (1)
    {
        read(STDIN_FILENO, &c, 1);

        // Handle backspace
        if (c == 127) // ASCII value of backspace
        {
            if (pos > 0)
            {
                write(STDOUT_FILENO, "\b \b", 3); // Erase character on screen
                pos--;
            }
        }
        else if (c == '\n') // Enter key
        {
            full_input[pos] = '\0';
            write(STDOUT_FILENO, "\n", 1);

            // Check if quotes are balanced
            unbalanced_quotes = !are_quotes_balanced(full_input);
            if (!unbalanced_quotes)
            {
                break; // Exit the loop when quotes are balanced
            }

            // Continue prompt for unbalanced quotes
            write(STDOUT_FILENO, "> ", 2);
        }
        else
        {
            full_input[pos] = c;
            write(STDOUT_FILENO, &c, 1);
            pos++;

            // Reallocate if input exceeds buffer size
            if (pos >= BUFFER_SIZE - 1)
            {
                buf_size *= 2;
                temp = realloc(full_input, buf_size);
                if (!temp)
                {
                    free(full_input);
                    disable_raw_mode(&orig_termios);
                    return NULL;
                }
                full_input = temp;
            }
        }
    }

    disable_raw_mode(&orig_termios);
    return full_input;
}
*/




char *get_full_input(void)
{
    char *input;
    char *full_input = NULL;
    char *temp;
    int unbalanced_quotes;

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

/*
// Function to handle input and ensure quotes are closed
char *get_full_input(void)
{
	char *input;
	char *full_input = NULL;
	char *temp;
	int unbalanced_quotes;

	 write(1, "\033[35mMSL> \033[0m", 14);

	while (1)
	{
		input = readline("");
		//input = get_next_line(STDIN_FILENO);
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
*/