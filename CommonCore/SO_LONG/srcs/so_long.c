#include "../headers/so_long.h"

int	controls(int key, t_data *data)
{
	int	i;
/*
//control keys
	if (key == 2 || key == 124)
		mv_right(data);
	else if (key == 0 || key == 123)
		mv_left(data);
	else if (key == 13 || key == 126)
		mv_up(data);
	else if (key == 1 || key == 125)
		mv_down(data);
	else */if (key == 53) //close window with escape
	{
		i = 0;

		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	return (0);
}

int	close_win(t_data data)
{
	int	i;

	i = 0;
	while (data.map[i])
		{
			free(data.map[i]);
			i++;
		}
		free(data.map);
		mlx_destroy_window(data.mlx, data.win);
		exit(1);
		return (0);
}

static void	init_data(t_data *data)
{
	data->collect = 0;
	data->mvmt = 0;
	data->win_w = ft_strlen(data->map[0]);
	data->win_h = map_height(data->map);
}

int	main(int argc, char **argv)
{
	t_data	data;
	/*
	if (argc < 2)
	{
		perror("ERROR");
		return (1);
	}*/
	data.win_w = 1920;
	data.win_h = 1080;
	data.mlx = mlx_init();

	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, data.win_w, data.win_h, "SO_LONG");
	if (!data.win)
		return (1);
	//mlx_key_hook(data.win, controls, &data);
	mlx_hook(data.win, 2, (1L << 0), controls, &data);
	mlx_hook(data.win, 17, (1L << 0), close_win, &data);
	mlx_loop(data.mlx);
	return (0);
}