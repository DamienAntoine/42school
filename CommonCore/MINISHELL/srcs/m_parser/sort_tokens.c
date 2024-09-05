#include "../../headers/minishell.h"

void	ft_sortpipes(t_data *data)
{
	t_command *current = data->commands;
	current->next = malloc(sizeof(t_command));	// if pipe, new command so alloc next struct node
	if (!current->next)
		return;
	current = current->next;					// move to next node
	memset(current, 0, sizeof(t_command));		// init new node
}

void	ft_sortredirect(t_data *data, int *i)
{
	t_token_list *toklist = data->toklist;
	//t_command *current = data->commands;

	if (ft_strcmp(toklist->tokens[*i], "<") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if there's a token after operator
			ft_add_redirection(data, toklist->tokens[*i], 0); // 0 for input
	}
	else if (ft_strcmp(toklist->tokens[*i], ">") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if there's a token after operator
			ft_add_redirection(data, toklist->tokens[*i], 1); // 1 for output
	}
	else if (ft_strcmp(toklist->tokens[*i], ">>") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if there's a token after operator
			ft_add_redirection(data, toklist->tokens[*i], 2); // 2 for append
	}
	else if (ft_strcmp(toklist->tokens[*i], "<<") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if there's a token after operator
			ft_add_redirection(data, toklist->tokens[*i], 3); // 3 for here-doc
	}
}

void	ft_sortloop(t_data *data, int i, int j)
{
	t_token_list *toklist = data->toklist;
	t_command *current = data->commands;

	current->args = malloc(sizeof(char *) * (toklist->token_count + 1)); // +1 for NULL termination
	if (!current->args)
		return;
	while (i < toklist->token_count)
	{
		if (ft_strcmp(toklist->tokens[i], " ") == 0)
			i++;

		// Handle pipes
		if (ft_strcmp(toklist->tokens[i], "|") == 0)
		{
			current->args[j] = NULL;
			ft_sortpipes(data); // Now using data instead of returning anything
			j = 0;
			current = current->next;
			current->args = malloc(sizeof(char *) * (toklist->token_count + 1));
			if (!current->args)
				return;
			i++;
		}

		// Handle redirection
		else if (ft_strcmp(toklist->tokens[i], "<") == 0 || 
				 ft_strcmp(toklist->tokens[i], ">") == 0 || 
				 ft_strcmp(toklist->tokens[i], ">>") == 0 || 
				 ft_strcmp(toklist->tokens[i], "<<") == 0)
		{
			ft_sortredirect(data, &i);
		}
		// Handle normal command tokens
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

void	ft_sort_tokens(t_data *data)
{
	int i = 0;
	int j = 0;

	ft_memset(data->commands, 0, sizeof(t_command));
	ft_sortloop(data, i, j);
}
