/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:13:20 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 15:27:34 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_sortpipes(t_command *commands)
{
	t_command	*current;

	current = commands;
	current->next = malloc(sizeof(t_command));
	if (!current->next)
		return ;
	memset(current->next, 0, sizeof(t_command));
}

int	ft_process_arguments(t_data *data, t_command **current, int *i, int *j)
{
	t_token_list	*toklist;

	toklist = data->toklist;
	if (data->state.last_exit_status != 0)
		return (-1);
	if (ft_strcmp(toklist->tokens[*i], "<") == 0
		|| ft_strcmp(toklist->tokens[*i], ">") == 0
		|| ft_strcmp(toklist->tokens[*i], ">>") == 0
		|| ft_strcmp(toklist->tokens[*i], "<<") == 0)
		return (ft_sortredirect(data, *current, i));
	else if (ft_strlen(toklist->tokens[*i]) > 0
		&& !ft_isspace(toklist->tokens[*i][0]))
	{
		if ((*current)->cmds == NULL)
			(*current)->cmds = ft_strdup(toklist->tokens[*i]);
		else
			(*current)->args[(*j)++] = ft_strdup(toklist->tokens[*i]);
		(*i)++;
	}
	else
		(*i)++;
	return (0);
}

int	allocate_and_process_args(t_data *data, t_command **current, int *i, int *j)
{
	t_token_list	*toklist;

	toklist = data->toklist;
	if (ft_strcmp(toklist->tokens[*i], "|") == 0)
	{
		(*current)->args[*j] = NULL;
		ft_sortpipes(*current);
		*j = 0;
		*current = (*current)->next;
		(*current)->args = malloc(sizeof(char *) * (toklist->token_count + 1));
		if (!(*current)->args)
			return (-1);
		(*i)++;
	}
	else
	{
		if (ft_process_arguments(data, current, i, j) == -1)
			return (-1);
	}
	return (0);
}

int	ft_sortloop(t_data *data, int i, int j)
{
	t_token_list	*toklist;
	t_command		*current;

	toklist = data->toklist;
	current = data->commands;
	current->args = malloc(sizeof(char *) * (toklist->token_count + 1));
	if (!current->args)
	{
		set_exit_status(1, data);
		return (-1);
	}
	current->args[0] = NULL;
	while (i < toklist->token_count)
	{
		if (data->state.last_exit_status != 0)
			return (-1);
		if (allocate_and_process_args(data, &current, &i, &j) == -1)
			return (-1);
	}
	current->args[j] = NULL;
	return (0);
}

int	ft_sort_tokens(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_memset(data->commands, 0, sizeof(t_command));
	if (ft_sortloop(data, i, j) == -1)
		return (-1);
	return (0);
}
