/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:19:30 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:19:31 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	perror_and_free(const char *message, void *ptr)
{
	if (message)
		perror(message);
	if (ptr)
		free(ptr);
}

void	printf_and_free(const char *message, void *ptr)
{
	if (message)
		printf("%s", message);
	if (ptr)
		free(ptr);
}
