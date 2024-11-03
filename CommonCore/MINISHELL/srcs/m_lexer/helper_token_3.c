/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_token_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:16:39 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:16:40 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	quote_check(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (c == '\"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
}

void	process_input(const char *input, char *result, size_t len,
		t_quote_state *quote_state)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		quote_check(input[i], &quote_state->in_single_quotes,
			&quote_state->in_double_quotes);
		if ((input[i] == '\'' && !(quote_state->in_double_quotes))
			|| (input[i] == '\"' && !(quote_state->in_single_quotes)))
			i++;
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
}

char	*remove_balanced_quotes(const char *input)
{
	char			*result;
	size_t			len;
	t_quote_state	quote_state;

	quote_state.in_single_quotes = 0;
	quote_state.in_double_quotes = 0;
	len = ft_strlen(input);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	process_input(input, result, len, &quote_state);
	return (result);
}
