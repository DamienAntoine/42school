/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_token_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:16:33 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:16:34 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

size_t	ft_estimate_variable_size(const char *str, int *i, t_data *data)
{
	int		start;
	char	*var_name;
	char	*expanded_var;
	size_t	size;

	size = 0;
	if (str[*i] == '?')
	{
		size += 11;
		(*i)++;
	}
	else
	{
		start = *i;
		while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		var_name = ft_substr(str, start, *i - start);
		expanded_var = expand_variable(var_name, data);
		size += ft_strlen(expanded_var);
		free(var_name);
		free(expanded_var);
	}
	return (size);
}

size_t	ft_estimate_buffer_size(const char *str, t_data *data)
{
	size_t	size;
	int		i;

	size = ft_strlen(str) + 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			size += ft_estimate_variable_size(str, &i, data);
		}
		else
			i++;
	}
	return (size);
}

size_t	estimate_buffer_size(const char *str, t_data *data)
{
	size_t	buffer_size;

	buffer_size = ft_estimate_buffer_size(str, data);
	return (buffer_size);
}
