/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:14:37 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 12:14:38 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	quotes_check(const char *input)
{
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (input[i] == '\"')
			in_double_quotes = !in_double_quotes;
		if (input[i] == '$')
		{
			if (in_double_quotes)
				return (0);
			if (in_single_quotes)
				return (1);
		}
		i++;
	}
	return (0);
}

void	process_quotes(const char *str, int *i, t_data *data)
{
	handle_single_quotes(str, i, data);
	handle_double_quotes(str, i, data);
}

int	is_in_quotes(const char *arg, int position)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (i < position)
	{
		if (arg[i] == '\'')
			in_quotes++;
		i++;
	}
	return (in_quotes % 2 != 0);
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
