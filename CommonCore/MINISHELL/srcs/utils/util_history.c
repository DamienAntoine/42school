/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:13:57 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 15:50:37 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_history	*add_command_to_history(t_history **history, const char *command)
{
	t_history	*tail;
	t_history	*new_node;

	new_node = malloc(sizeof(t_history));
	if (!new_node)
		return (NULL);
	new_node->command = ft_strdup(command);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*history == NULL)
		*history = new_node;
	else
	{
		tail = *history;
		while (tail->next)
			tail = tail->next;
		tail->next = new_node;
		new_node->prev = tail;
	}
	add_history(command);
	return (new_node);
}
