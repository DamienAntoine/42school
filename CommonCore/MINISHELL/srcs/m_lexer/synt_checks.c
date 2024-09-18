#include "../../headers/minishell.h"

//maybe add max length,
int	has_synt_errors(t_token_list *toklist)
{
	int	synt_result;

	synt_result = ft_check_syntax(toklist);
	if (synt_result != 0)
	{
		if (synt_result == ERPIPE)
			printf("SYNTAX ERROR: Pipe misplaced");
		else if (synt_result == ERCONS)
			printf("SYNTAX ERROR: Consecutive operators");
		else if (synt_result == ERREDIR)
			printf("SYNTAX ERROR: Redirection at the start or end of the command line");
		else if (synt_result == ERTOKEN)
			printf("SYNTAX ERROR: No token after operator");
		else if (synt_result == ERQUOTE)
			printf("SYNTAX ERROR: Unmatched quotes");
		else if (synt_result == ERVARN)
			printf("SYNTAX ERROR: Invalid Env variable name");
		return (1);
	}
	else
		return (0);
}

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
			if (i == 0 || i == toklist->token_count - 1)
				return (ERPIPE); // syntax error for pipe at start/end
			else if (is_consecutive(toklist, i) == 1)
				return (ERCONS); // syntax error for consecutive pipes
		}
		//redir syntax
		if (ft_strcmp(toklist->tokens[i], "<") == 0 || ft_strcmp(toklist->tokens[i], ">") == 0 || \
		ft_strcmp(toklist->tokens[i], "<<") == 0 || ft_strcmp(toklist->tokens[i], ">>") == 0)
		{
			if (i == 0 || i == toklist->token_count - 1)
				return (ERREDIR);
			else if (is_consecutive(toklist, i) == 1)
				return (ERCONS);
			else if (is_consecutive(toklist, i) == 2)
				return (ERTOKEN);
		}
		//env var expansion
		if (toklist->tokens[i][0] == '$' && !is_valid_env_variable(toklist->tokens[i] + 1))
			return (ERVARN); // Syntax error: invalid environment variable

		i++;
	}
	return (0);
}


