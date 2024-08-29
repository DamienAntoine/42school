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
				return (ERPIPE); // Syntax error for consecutive pipes or pipe at start/end
			else if (consecutive_check(toklist, ++i) == 1)
				return (ERCONS);
			else if (consecutive_check(toklist, ++i) == 2)
				return (ERTOKEN);
		}

		//redir syntax
		if (ft_strcmp(toklist->tokens[i], "<") == 0 || ft_strcmp(toklist->tokens[i], ">") == 0 || \
		ft_strcmp(toklist->tokens[i], "<<") == 0 || ft_strcmp(toklist->tokens[i], ">>") == 0)
		{
			if (i == 0 || i == toklist->token_count)
				return (ERREDIR);
			else if (consecutive_check(toklist, ++i) == 1)
				return (ERCONS);
			else if (consecutive_check(toklist, ++i) == 2)
				return (ERTOKEN);
		}

		//quotes syntax
		if ((ft_strcmp(toklist->tokens[i], "\'") == 0) || (ft_strcmp(toklist->tokens[i], "\"") == 0))
		{
			if (check_quotes == 1)
				return (ERQUOTE);
		}

		//env var expansion
		if (toklist->tokens[i][0] == '$' && !is_valid_env_variable(toklist->tokens[i]))
			return (ERVARN); // Syntax error: invalid environment variable

		i++;
	}
	return (0);
}
//maybe add max length,

int	is_valid_env_variable(const char *var) //only checks if env var has valid syntax, not if the variable exists
{
	int	i;

	i = 0;
	if (var[1] == '\0')
		return (1);
	while (var[i])
	{
		if (!isalnum(var[i]) && var[i] != '_')
			return (1);
	}
}

int	check_quotes(t_token_list *toklist)
{
	int	singquote;
	int	doubquote;
	int	i;

	singquote = 0;
	doubquote = 0;
	i = 0;
	while (toklist->tokens[i])
	{
		if (ft_strcmp(toklist->tokens[i], "\'") && doubquote == 0)
			singquote = !singquote;
		else if (ft_strcmp(toklist->tokens[i], "\"") && singquote == 0)
		doubquote = !doubquote;
	}
	if (singquote || doubquote)
		return (1);
	return (0);
}

//checks if two consecutive operators
int consecutive_check(t_token_list *toklist, int i)
{
	char *operators[6];
	int j;

	operators[0] = "|"; //need a better way to do this
	operators[1] = "<";
	operators[2] = ">";
	operators[3] = "<<";
	operators[4] = ">>";
	operators[5] = NULL;
	j = 0;
	if (i >= toklist->token_count || !toklist->tokens[i])
		return (2);
	while (operators[j] != NULL)
	{
		if (ft_strcmp(toklist->tokens[i], operators[j]) == 0) //if current token is an operator, means there are two operators in a row
			return (1); // Invalid: operator cannot be a filename
		j++;
    }
	return (0);
} //next: if file doesnt exist and '>': create file. if '<': error. if '>>': create file. if '<<': ??

int	synt_errors_check(t_token_list *toklist)
{
	int	synt_result;

	synt_result = ft_check_syntax(toklist);
	if (synt_result == ERPIPE)
	{
		printf("SYNTAX ERROR: Pipe misplaced");
		return (1);
	}
	else if (synt_result == ERCONS)
	{
		printf("SYNTAX ERROR: Consecutive operators");
	}
	else if (synt_result == ERREDIR)
	{
		printf("SYNTAX ERROR: Redirection at the start or end of the command line");
		return (1);
	}
	else if (synt_result == ERTOKEN)
	{
		printf("SYNTAX ERROR: No token after operator");
		return (1);
	}
	else if (synt_result == ERQUOTE)
	{
		printf("SYNTAX ERROR: Unmatched quotes");
		return (1);
	}
	else if (synt_result == ERVARN)
	{
		printf("SYNTAX ERROR: Invalid Env variable name");
		return (1);
	}
		return (0);
}
