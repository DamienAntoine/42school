/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_token_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:16:36 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:16:37 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_single_quotes(const char *str, int *i, t_data *data)
{
	if (str[*i] == '\'' && !data->env->in_double_quotes)
	{
		data->env->in_single_quotes = !data->env->in_single_quotes;
		(*i)++;
	}
}

void	handle_double_quotes(const char *str, int *i, t_data *data)
{
	if (str[*i] == '\"')
	{
		data->env->in_double_quotes = !data->env->in_double_quotes;
		(*i)++;
	}
}

void	handle_unprocessed_string(const char *str, int *i, int *start,
		t_data *data)
{
	char	*temp;

	if (*i > *start)
	{
		temp = ft_substr(str, *start, *i - *start);
		ft_strlcat(data->env->result, temp, data->env->buffer_size);
		free(temp);
	}
}

char	*expand_variable(const char *var_name, t_data *data)
{
	char	*value;

	if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup(""));
	value = find_env_value(data->env, var_name);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}
