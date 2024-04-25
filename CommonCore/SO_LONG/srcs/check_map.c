#include "../headers/so_long.h"

void    clean_map(t_data ***data)
{
    int	x;

	x = 0;
	while ((**data)->map[x])
	{
		free((**data)->map[x]);
		x++;
	}
	free((**data)->map);
}

static void	is_rectangle(t_data **data)
{
    int y_map;
    int x_map;
    int height;
    int temp;

    y_map = 0;
    temp = 0;
    height = map_height((*data)->map);
    while (y_map != height)
    {
        x_map = 0;
        while ((*data)->map[y_map][x_map])
            x_map++;
        y_map++;
        if (temp)
        {
            if (temp != x_map)
                perror("ERROR: Map is not rectangular");
        }
        else
            temp = x_map;
    }
}

static int check_walls(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1')
            return (1);
        i++;
    }
    return (0);
}

static void check_surr_walls(t_data **data)
{
    int i;

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

void	wrong_element(t_data ***data)
{
	int	x;

	x = 0;
	while ((**data)->map[x])
	{
		free((**data)->map[x]);
		x++;
	}
	free((**data)->map);
	perror("ERROR: Wrong element");
}

void	check_elem(t_data **data)
{
	t_map_data	map_data;

	map_data.c = 0;
	map_data.p = 0;
	map_data.e = 0;
	map_data.y = map_height((*data)->map) - 1;
	while (map_data.y--)
	{
		map_data.x = 0;
		while ((*data)->map[map_data.y][map_data.x] != '\0')
		{
			if ((*data)->map[map_data.y][map_data.x] == 'E')
				map_data.e++;
			else if ((*data)->map[map_data.y][map_data.x] == 'P')
				map_data.p++;
			else if ((*data)->map[map_data.y][map_data.x] == 'C')
				map_data.c++;
			else if ((*data)->map[map_data.y][map_data.x] != '1' &&
				(*data)->map[map_data.y][map_data.x] != '0')
				wrong_element(&data);
			map_data.x++;
		}
	}
	if (map_data.c == 0 || map_data.p == 0 || map_data.e == 0 || map_data.p > 1)
    {
		clean_map(&data);
        perror("ERROR: Map elements are incorrect");
    }
}

//1 sortie, 1 piece, 1 spawn

void    check_map(t_data *data)
{
    is_rectangle(&data);
	check_elem(&data);
    check_surr_walls(&data);
}