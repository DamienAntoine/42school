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
	else if (ft_strcmp(toklist->tokens[*i], "<<") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if theres a token after operator
			ft_add_redirection(current, toklist->tokens[*i], 3);
			// "<< should be given a delimiter, then read the input until a line containing thedelimiter is seen.
			//However, it doesn’t have to update the history!" (whatever that means)
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
        if (ft_strcmp(toklist->tokens[i], " ") == 0)
            i++;
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
			current = ft_sortpipes(current);
		else if (ft_strcmp(toklist->tokens[i], "<") == 0 || ft_strcmp(toklist->tokens[i], ">") == 0 || ft_strcmp(toklist->tokens[i], ">>") == 0)
			current = ft_sortredirect(toklist, current, &i);
		else if (ft_strlen(toklist->tokens[i]) > 0 && !ft_isspace(toklist->tokens[i][0]))
		{
			if (current->cmds == NULL)
				current->cmds = ft_strdup(toklist->tokens[i]);
			else
				current->args[j++] = ft_strdup(toklist->tokens[i]);
            i++;
		}
        else
		    i++;
	}
	current->args[j] = NULL;
}


//every strdup will need a free at some point
t_command	*ft_sort_tokens(t_token_list *toklist, t_command *table)
{
	int         i;
	int         j;
	t_command   *current;

	i = 0;
	j = 0;
	current = table;
    ft_memset(current, 0, 1);
	ft_sortloop(toklist, current, i, j);
	return (table);
}
//FUNCTION NEEDS TO BE TESTED
