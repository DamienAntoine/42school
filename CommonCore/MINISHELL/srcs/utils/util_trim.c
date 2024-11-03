/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:19:21 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:19:21 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*trim_input(char *input)
{
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, " \t\n\r");
	if (!trimmed_input || *trimmed_input == '\0')
	{
		free(trimmed_input);
		return (NULL);
	}
	return (trimmed_input);
}
