#include "../../headers/minishell.h"

//we need a function to check syntax here (cant use two pipes in a row without a command between, ...)

t_command	*ft_sort_tokens(t_token_list *toklist)
{
	int	i;
	int	j;
	t_command *table;
	t_command *current;

	table = malloc(sizeof(t_command));
	current = table;
	i = 0;
	j = 0;

	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_command));				// init first struct node
	while (i < toklist->token_count)
	{
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
		{
			current->next = malloc(sizeof(t_command));	// if pipe, new command so alloc next struct node
			if (!current->next)
				return (NULL);
			current = current->next;					// move to next node
			memset(current, 0, sizeof(t_command));		// init new node
			j = 0;
		}
		else if (ft_strcmp(toklist->tokens[i], "<") == 0)
		{
			if (++i < toklist->token_count)				// check if theres a token after <
				current->input_redirect = ft_strdup(toklist->tokens[i]);
		}
		else if (ft_strcmp(toklist->tokens[i], ">") == 0)
		{
			if (++i < toklist->token_count)				// check if theres a token after >
				current->output_redirect = ft_strdup(toklist->tokens[i]);
		}
		else if (ft_strcmp(toklist->tokens[i], ">>") == 0)
		{
			current->append = 1;
			if (++i < toklist->token_count)				// check if theres a token after >>
				current->output_redirect = ft_strdup(toklist->tokens[i]);
		}
		else
		{
			if (current->cmds == NULL)
				current->cmds = ft_strdup(toklist->tokens[i]);		// first token that is not a >, |, <, ... is the command
			else
				current->args[j++] = ft_strdup(toklist->tokens[i]);	// all other similar tokens are arguments (need to double check this part but should work for now)
		}
		i++;
	}
	current->args[j] = NULL;
	return (table);
}
//FUNCTION NEEDS TO BE TESTED
//we need to shorten this function somehow
