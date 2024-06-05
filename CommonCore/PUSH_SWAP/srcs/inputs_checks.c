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
	if ((c >= '0' && c <= '9') || c == ' ' || c == '+' || c == '-')
	{
		return (1);
	}
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
			if (!ft_isdigit(input[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_plus_sign(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	check_splitarg(char **splitarg)
{
    int		j;
    long	num;

    j = 0;
    while (splitarg[j])
    {
        if (check_plus_sign(splitarg[j]))
        {
            free_args(splitarg);
            return (0);
        }
        num = ft_atol(splitarg[j]);
        if (num > INT_MAX || num < INT_MIN)
        {
            free_args(splitarg);
            return (0);
        }
        j++;
    }
    free_args(splitarg);
    return (1);
}

int	check_int_limits(char **input)
{
    int		i;
    char	**splitarg;

    i = 1;
    while (input[i])
    {
        splitarg = ft_split(input[i], ' ');
        if (splitarg == NULL)
            return (0);
        if (!check_splitarg(splitarg))
            return (0);
        i++;
    }
    return (1);
}
