/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:19:06 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:19:07 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	reset_command(t_data *data)
{
	free_command(data->commands);
	data->commands = malloc(sizeof(t_command));
	if (!data->commands)
	{
		perror("Failed to allocate memory for new commands");
		exit(EXIT_FAILURE);
	}
	init_commands(data);
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	reset_toklist(t_data *data)
{
	if (data->toklist->tokens)
	{
		free_tokens(data->toklist->tokens);
		data->toklist->tokens = NULL;
		data->toklist->token_count = 0;
	}
}
