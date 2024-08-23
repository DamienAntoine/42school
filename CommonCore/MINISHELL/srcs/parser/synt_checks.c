#include "../../headers/minishell.h"

//we need a function to check syntax here (cant use two pipes in a row without a command between, ...)
int ft_check_syntax(t_token_list *toklist)
{
	int i;

	i = 0;
	while (i < toklist->token_count)
	{
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
		{
			if (i == 0 || i == toklist->token_count - 1 || ft_strcmp(toklist->tokens[i + 1], "|") == 0)
				return (-1); // Syntax error for consecutive pipes or pipe at start/end
		}
		// more syntax checks here (redirection checks would check if there is a file after a '>' for example, and not someting like "cmd < > file" or "cmd > < file")
		i++;
	}
	return (0);
}

void	synt_errors_check(t_token_list *toklist)
{
	if (ft_check_syntax(toklist) == -1)
	{
		printf("SYNTAX ERROR: Pipes misplaced");
		return (1);
	}
}
