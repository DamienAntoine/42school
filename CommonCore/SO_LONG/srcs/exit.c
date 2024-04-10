#include "../headers/so_long.h"


void	exit_door(t_data ***data)
{
	int	x;

	x = 0;
	while ((**data)->map[x])
	{
		free((**data)->map[x]);
		x++;
	}
	free((**data)->map);
	mlx_destroy_window((**data)->mlx, (**data)->win);
	exit(1);
}