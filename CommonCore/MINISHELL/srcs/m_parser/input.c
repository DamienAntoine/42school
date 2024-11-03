/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:13:16 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 12:13:16 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	balance_helper(int first_quote, const char *input, int i)
{
	if (first_quote == 1)
	{
		if (input[i] == '\'' && (input[i - 1] != '\\'))
			return (0);
		else
			return (1);
	}
	else if (first_quote == 2)
	{
		if (input[i] == '\"' && (input[i - 1] != '\\'))
			return (0);
		else
			return (2);
	}
	else
		return (85654);
}

int	are_quotes_balanced(const char *input)
{
	int	i;
	int	first_quote;

	i = 0;
	first_quote = 0;
	while (input[i])
	{
		if (first_quote == 0)
		{
			if (input[i] == '\'' && (input[i - 1] != '\\'))
				first_quote = 1;
			else if (input[i] == '\"' && (input[i - 1] != '\\'))
				first_quote = 2;
		}
		else
			first_quote = balance_helper(first_quote, input, i);
		i++;
	}
	return (first_quote == 0);
}

char	*read_and_free_input(char **full_input)
{
	char	*input;

	input = readline("\033[35m> \033[0m");
	if (input == NULL)
	{
		free(*full_input);
		return (NULL);
	}
	return (input);
}

char	*append_input(char *full_input, const char *input)
{
	char	*temp;
	char	*new_full_input;

	temp = full_input;
	new_full_input = ft_strjoin(temp, "\n");
	free(temp);
	temp = new_full_input;
	new_full_input = ft_strjoin(temp, input);
	free(temp);
	return (new_full_input);
}

char	*get_full_input(void)
{
	char	*input;
	char	*full_input;
	int		unbalanced_quotes;

	full_input = NULL;
	input = readline("\033[35mMSL> \033[0m");
	if (input == NULL)
		return (NULL);
	full_input = ft_strdup(input);
	free(input);
	unbalanced_quotes = !are_quotes_balanced(full_input);
	while (unbalanced_quotes)
	{
		input = read_and_free_input(&full_input);
		if (input == NULL)
			return (NULL);
		full_input = append_input(full_input, input);
		free(input);
		unbalanced_quotes = !are_quotes_balanced(full_input);
	}
	return (full_input);
}
