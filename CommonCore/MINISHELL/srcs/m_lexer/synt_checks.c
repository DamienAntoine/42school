#include "../../headers/minishell.h"

int	is_redirection(t_token_list *toklist, int i)
{
	if (ft_strcmp(toklist->tokens[i], "<") == 0 || ft_strcmp(toklist->tokens[i],
			">") == 0 || ft_strcmp(toklist->tokens[i], "<<") == 0
		|| ft_strcmp(toklist->tokens[i], ">>") == 0)
		return (1);
	return (0);
}

int	ft_check_syntax(t_token_list *toklist)
{
	int	i;

	i = 0;
	while (i < toklist->token_count)
	{
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
		{
			if (i == 0 || i == toklist->token_count - 1)
				return (ERPIPE);
			else if (is_consecutive(toklist, i) == 1)
				return (ERCONS);
		}
		if (is_redirection(toklist, i) == 1)
		{
			if (i == 0 || i == toklist->token_count - 1)
				return (ERREDIR);
			else if (is_consecutive(toklist, i) == 1)
				return (ERCONS);
			else if (is_consecutive(toklist, i) == 2)
				return (ERTOKEN);
		}
		i++;
	}
	return (0);
}
