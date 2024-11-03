/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:14:37 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 15:22:21 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	process_quotes(const char *str, int *i, t_data *data)
{
	handle_single_quotes(str, i, data);
	handle_double_quotes(str, i, data);
}

char	*handle_quotes(const char *str, t_data *data)
{
	char	*expanded_str;
	char	*result;

	expanded_str = process_env_token(str, data);
	result = remove_balanced_quotes(expanded_str);
	free(expanded_str);
	return (result);
}
