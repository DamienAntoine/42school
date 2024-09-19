#include "../../headers/minishell.h"

int	is_pipe(t_data *data)
{
	t_token_list	*toklist;
	int				i;

	toklist = data->toklist;
	i = 0;
	while (toklist->tokens[i])
	{
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "cat") == 0
		|| ft_strcmp(cmd, "grep") == 0)
	{
		return (1);
	}
	return (0);
}

int	is_valid_env_variable(const char *var) //only checks if env var has valid syntax, not if the variable exists
{
	int	i;

	i = 0;
	if (var == NULL || var[0] == '\0')
		return (1);
	if (var[0] == '?' && var[1] == '\0')
		return (1);
	if (!ft_isalnum(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
    return (1);
}

int	has_quotes(t_token_list *toklist)
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

int is_operator(const char *token)
{
    if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "<") == 0 ||
        ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<<") == 0 ||
        ft_strcmp(token, ">>") == 0)
    {
        return 1;
    }
    return 0;
}

int is_consecutive(t_token_list *toklist, int i)
{
    if (i + 1 >= toklist->token_count)
        return 2; // Ensure there's a next token

    if (is_operator(toklist->tokens[i]) && is_operator(toklist->tokens[i + 1]))
        return 1; // Consecutive operators

    return 0; // No consecutive operators
}
/*
//checks if two consecutive operators
int is_consecutive(t_token_list *toklist, int i)
{
	char *operators[6];
	int j;
	int	k;

	operators[0] = "|"; //need a better way to do this
	operators[1] = "<";
	operators[2] = ">";
	operators[3] = "<<";
	operators[4] = ">>";
	operators[5] = NULL;
	j = 0;
	k = 0;
	if (i + 1 >= toklist->token_count)
		return (2); // ensure there's a next token
	while (operators[j] != NULL)
	{
		if (ft_strcmp(toklist->tokens[i], operators[j]) == 0) //current token is operator
		{
			k = 0;
			while (operators[k] != NULL)
			{
				if (ft_strcmp(toklist->tokens[i + 1], operators[k]) == 0)
					return (1); // consecutive op
				k++;
			}
			return (0);//i changed return (1) to (0) // Invalid: operator cannot be a filename
		}
		j++;
	}
	return (0);
} //next: if file doesnt exist and '>': create file. if '<': error. if '>>': create file. if '<<': ??
*/