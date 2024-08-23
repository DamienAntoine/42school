#include "../../headers/minishell.h"

t_command	*ft_sortpipes(t_command *current)
{
	current->next = malloc(sizeof(t_command));	// if pipe, new command so alloc next struct node
	if (!current->next)
		return (NULL);
	current = current->next;					// move to next node
	memset(current, 0, sizeof(t_command));		// init new node
	return (current);
}

t_command *ft_sortredirect(t_token_list *toklist, t_command *current, int *i)
{
	if (ft_strcmp(toklist->tokens[*i], "<") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if theres a token after operator
			ft_add_redirection(current, toklist->tokens[*i], 0); // 0 for input
	}
	else if (ft_strcmp(toklist->tokens[*i], ">") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if theres a token after operator
			ft_add_redirection(current, toklist->tokens[*i], 1); // 1 for output
	}
	else if (ft_strcmp(toklist->tokens[*i], ">>") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if theres a token after operator
			ft_add_redirection(current, toklist->tokens[*i], 2); // 2 for append
	}
	return (current);
}

void	ft_sortloop(t_token_list *toklist, t_command *current, int i, int j)
{
	current->args = malloc(sizeof(char *) * (toklist->token_count + 1)); // +1 for NULL termination
	if (!current->args)
		return;
	while (i < toklist->token_count)
	{
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
			current = ft_sortpipes(current);
		else if (ft_strcmp(toklist->tokens[i], "<") == 0 || ft_strcmp(toklist->tokens[i], ">") == 0 || ft_strcmp(toklist->tokens[i], ">>") == 0)
			current = ft_sortredirect(toklist, current, &i);
		else
		{
			if (current->cmds == NULL)
				current->cmds = ft_strdup(toklist->tokens[i]);
			else
				current->args[j++] = ft_strdup(toklist->tokens[i]);
		}
		i++;
	}
	current->args[j] = NULL;
}
//every strdup will need a free at some point
t_command	*ft_sort_tokens(t_token_list *toklist)
{
	int	i;
	int	j;
	t_command *table;
	t_command *current;

	i = 0;
	j = 0;
	table = malloc(sizeof(t_command));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_command));				// init first struct node
	current = table;
	ft_sortloop(toklist, current, i, j);
	return (table);
}
//FUNCTION NEEDS TO BE TESTED
