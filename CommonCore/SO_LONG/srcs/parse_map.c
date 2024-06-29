/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:20:49 by dantoine          #+#    #+#             */
/*   Updated: 2024/05/02 16:20:50 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**parse_map(char *map)
{
	char	*cur_line;
	char	*all_lines;
	char	*temp;
	char	**split_lines;
	int		fd;

	cur_line = "";
	all_lines = ft_strdup("");
	if (!all_lines)
		return (NULL);
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		perror("ERROR: Couldn't open fd");
		free(all_lines);
		return (NULL);
	}
	while ((cur_line = get_next_line(fd)) != NULL && cur_line[0] != '\n')
	{
		temp = all_lines;
        all_lines = ft_strjoin(all_lines, cur_line);
		free(temp);
        free(cur_line);
    }
	if(cur_line)
		free(cur_line);
	close(fd);
	if (all_lines[0] == '\0')
	{
		perror("ERROR: Selected map is NULL");
		free(all_lines);
		return (NULL);
	}
	split_lines = ft_split(all_lines, '\n');
	free(all_lines);
	return (split_lines);
}
