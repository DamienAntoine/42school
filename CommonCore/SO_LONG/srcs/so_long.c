/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:05:00 by dantoine          #+#    #+#             */
/*   Updated: 2024/05/02 14:07:04 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include <stdio.h>
#include <stdlib.h>

void	render_map(t_data *data)
{
	int		y1;
	int		y_map;
	int		backup_w;
	int		x1;
	int		x_map;

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
	data->mlx = mlx_init();
	data->img = NULL;
	data->win = NULL;
}

void free_resources(t_data *data)
{
    int i = 0;

    if (data->map)
    {
        while (data->map[i])
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
    }
    if (data->img)
    {
        mlx_destroy_image(data->mlx, data->img);
        data->img = NULL;
    }
    if (data->win)
    {
        mlx_destroy_window(data->mlx, data->win);
        data->win = NULL;
    }
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        data->mlx = NULL;
    }
}

int	controls(int key, t_data *data)
{
	if (key == 65363 || key == 100)
		mv_right(&data);
	else if (key == 65361 || key == 97)
		mv_left(&data);
	else if (key == 65362 || key == 119)
		mv_up(&data);
	else if (key == 65364 || key == 115)
		mv_down(&data);
	else if (key == 65307)
		close_win(data);
	return (0);
}

int	close_win(t_data *data)
{
	free_images(data);
	free_resources(data);
	exit(EXIT_SUCCESS);
	return (0);
}

void free_images(t_data *data)
{
    if (data->img)
	{
        mlx_destroy_image(data->mlx, data->img);
        data->img = NULL;
    }
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
	{
		perror("Error: Not enough arguments");
		return (1);
	}
	check_file(argv[1]);
	data.map = parse_map(argv[1]);
	if (data.map != NULL)
	{
		check_map(&data);
		init_data(&data);
		data.win = mlx_new_window(data.mlx, data.win_w * 50, data.win_h * 50, "SO_LONG");
		if (!data.win)
		{
			free_resources(&data);
			return (1);
		}
		render_map(&data);
		mlx_hook(data.win, 2, (1L << 0), controls, &data);
		mlx_hook(data.win, 17, (1L << 0), close_win, &data);
		mlx_string_put(data.mlx, data.win, 5, 10, 0xffffff, "Move: 0");
		mlx_loop(data.mlx);
	}
	free_resources(&data);
	return (0);
}


