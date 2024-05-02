/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:14:47 by dantoine          #+#    #+#             */
/*   Updated: 2024/05/02 16:14:48 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	check_walls(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	check_surr_walls(t_data **data)
{
	int		i;

	if (check_walls((*data)->map[0]))
	{
		clean_map(&data);
		perror("ERROR: Map not surrounded by walls");
	}
	i = map_height((*data)->map) - 1;
	while (i)
	{
		if ((*data)->map[i][0] != '1' ||
			(*data)->map[i][ft_strlen((*data)->map[i]) - 1] != '1')
		{
			clean_map(&data);
			perror("ERROR: Map not surrounded by walls");
		}
		i--;
	}
	if (check_walls((*data)->map[map_height((*data)->map) - 1]))
	{
		clean_map(&data);
		perror("ERROR: Map not surrounded by walls");
	}
}
