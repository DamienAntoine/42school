/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:28:46 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/21 14:34:11 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

int	ft_strncmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	{
		while (s1[i] != '\0' || s2[i] != '\0')
		{
			if (s1[i] != s2[i])
			{
				if (s1[i] > s2[i])
					return (1);
				else
					return (-1);
			}
			i++;
		}
	}
	return (0);
}

void	ft_swap_str(char **a, char **b, int *sorter)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
	*sorter = 1;
}

int	main(int argc, char *argv[])
{
	int		sorter;
	int		i;

	sorter = 1;
	while (sorter != 0)
	{
		sorter = 0;
		i = 1;
		while (i < argc - 1)
		{
			if (ft_strncmp(argv[i], argv[i + 1]) > 0)
			{
				ft_swap_str(&argv[i], &argv[i + 1], &sorter);
			}
			i++;
		}
	}
	i = 1;
	while (i < argc)
	{
		ft_putstr(argv[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}
