#include "../headers/so_long.h"
#include <stdio.h>

int	controls(int key, t_data *data)
{
	int	i;

//control keys
	if (key == 65363 || key == 100)
		mv_right(&data);
	else if (key == 65361 || key == 97)
		mv_left(&data);
	else if (key == 65362 || key == 119)
		mv_up(&data);
	else if (key == 65364 || key == 115)
		mv_down(&data);
	else if (key == 65307) //close window with escape
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

void	render_map(t_data *data)
{
	int	y1;
	int	y_map;
	int	backup_w;
	int	x1;
	int	x_map;

	y1 = 0;
	y_map = 0;
	backup_w = data->win_w;
	while (data->win_h > 0)
	{
		x1 = 0;
		x_map = 0;
		while (data->win_w > 0)
		{
			print_elem(data->map[y_map][x_map], x1, y1, &data);
			x_map++;
			x1 += 50;
			data->win_w--;
		}
		data->win_w = backup_w;
		y_map++;
		y1 += 50;
		data->win_h--;
	}
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

	if (argc < 2)
	{
		perror("ERROR");
		return (1);
	}
	(void)argv;
	check_file(argv[1]);
	data.map = parse_map(argv[1]);
	if (data.map != NULL)
	{
		check_map(&data);
		init_data(&data);

		data.mlx = mlx_init();
		if (!data.mlx)
			return (1);

		data.win = mlx_new_window(data.mlx, data.win_w * 50, data.win_h * 50, "SO_LONG");
		if (!data.win)
			return (1);

		render_map(&data);
		mlx_hook(data.win, 2, (1L << 0), controls, &data);
		mlx_hook(data.win, 17, (1L << 0), close_win, &data);
		mlx_string_put(data.mlx, data.win, 5, 10, 0xffffff, "Move: 0");
		mlx_loop(data.mlx);
	}
	return (0);
}