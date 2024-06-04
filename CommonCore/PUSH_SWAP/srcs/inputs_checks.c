/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:51:48 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/04 14:52:14 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == ' ')
	{
		return (1);
	}
	return (0);
}

int	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

int	check_inputs(int argc, char **input)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!check_int_limits(input))
		return (0);
	while (i < argc)
	{
		j = 0;
		while (input[i][j] != '\0')
		{
			if (!ft_isdigit(input[i][j]) || ft_issign(input[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	sign;
	long	result;
	long	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	check_int_limits(char **input)
{
	int		i;
	int		j;
	long	num;
	char	**splitarg;

	i = 1;
	while (input[i])
	{
		splitarg = ft_split(input[i], ' ');
		if (splitarg == NULL)
			return (0);
		j = 0;
		while (splitarg[j])
		{
			num = ft_atol(splitarg[j]);
			if (num > INT_MAX || num < INT_MIN)
				return (0);
			j++;
		}
		free_args(splitarg);
		i++;
	}
	return (1);
}
