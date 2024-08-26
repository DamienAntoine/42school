#include "../../headers/minishell.h"

//we need a function to check syntax here (cant use two pipes in a row without a command between, ...)
int	ft_check_syntax(t_token_list *toklist)
{
	int	i;

	i = 0;
	while (i < toklist->token_count)
	{
		//pipe syntax
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
		{
			//if 1st token is pipe || pipe is last token || two pipes in a row not separated by a cmd
			if (i == 0 || i == toklist->token_count - 1 || ft_strcmp(toklist->tokens[i + 1], "|") == 0)
				return (-1); // Syntax error for consecutive pipes or pipe at start/end
		}

		//redir syntax
		if (ft_strcmp(toklist->tokens[i], "<") == 0 || ft_strcmp(toklist->tokens[i], ">") == 0 || \
		ft_strcmp(toklist->tokens[i], "<<") == 0 || ft_strcmp(toklist->tokens[i], ">>") == 0)
		{
			if (i == 0 || i == toklist->token_count || redir_check(toklist, ++i) == 1)
				return (-2);
		}

		// more syntax checks here (redirection checks would check if there is a file after a '>' for example, and not someting like "cmd < > file" or "cmd > < file")
		i++;
	}
	return (0);
}

int redir_check(t_token_list *toklist, int i)
{
	if (i >= toklist->token_count || !toklist->tokens[i])
		return (1);
	return (0);
} //next: if file doesnt exist and '>': create file. if '<': error. if '>>': create file. if '<<': ??

int	synt_errors_check(t_token_list *toklist)
{
	int	synt_result;

	synt_result = ft_check_synthax(toklist);
	if (synt_result == -1)
	{
		printf("SYNTAX ERROR: Pipe misplaced");
		return (1);
	}
	else if (synt_result == -2)
	{
		printf("SYNTAX ERROR: Redirection misplaced");
	}
	else
		return (0);
}
