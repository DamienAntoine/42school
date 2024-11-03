/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:19:24 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:19:25 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "pwd") == 0)
		return (1);
	return (0);
}

int	is_valid_env_variable(const char *var)
{
	int	i;

	i = 0;
	if (var == NULL || var[0] == '\0')
		return (1);
	if (var[0] == '?' && var[1] == '\0')
		return (1);
	if (!ft_isalnum(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	has_quotes(t_token_list *toklist)
{
	int	singquote;
	int	doubquote;
	int	i;

	singquote = 0;
	doubquote = 0;
	i = 0;
	while (toklist->tokens[i])
	{
		if (ft_strcmp(toklist->tokens[i], "\'") && doubquote == 0)
			singquote = !singquote;
		else if (ft_strcmp(toklist->tokens[i], "\"") && singquote == 0)
			doubquote = !doubquote;
	}
	if (singquote || doubquote)
		return (1);
	return (0);
}

int	is_operator(const char *token)
{
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<<") == 0
		|| ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}

int	is_consecutive(t_token_list *toklist, int i)
{
	if (i + 1 >= toklist->token_count)
		return (2);
	if (is_operator(toklist->tokens[i]) && is_operator(toklist->tokens[i + 1]))
		return (1);
	return (0);
}
