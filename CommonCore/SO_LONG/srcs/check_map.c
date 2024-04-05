#include "../headers/so_long.h"

int	is_rectangle(t_data **data)
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

//entoure de murs

//1 sortie, 1 piece, 1 spawn

void    check_map(t_data *data)
{
    is_rectangle(&data);
}