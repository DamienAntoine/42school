/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:45:50 by dantoine          #+#    #+#             */
/*   Updated: 2024/05/02 15:45:55 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static void	coins(t_data ***data)
{
	int		img_w;
	int		img_h;

	(**data)->collect--;
	(**data)->map[((**data)->y_p / 50)][((**data)->x_p / 50)] = '0';
	(**data)->img = mlx_xpm_file_to_image((**data)->mlx, \
	"./sprites/stolenfloor.xpm", &img_w, &img_h);
	mlx_put_image_to_window((**data)->mlx, (**data)->win, \
	(**data)->img, (**data)->x_p, (**data)->y_p);
}

void	mv_up(t_data **data)
{
	int		img_w;
	int		img_h;

	(*data)->img = mlx_xpm_file_to_image((*data)->mlx, \
	"./sprites/stolenfloor.xpm", &img_w, &img_h);
	mlx_put_image_to_window((*data)->mlx, (*data)->win, \
	(*data)->img, (*data)->x_p, (*data)->y_p);
	if ((*data)->map[((*data)->y_p / 50) - 1][((*data)->x_p / 50)] == 'E')
	{
		if ((*data)->collect <= 0)
			exit_door(&data);
	}
	else if ((*data)->map[((*data)->y_p / 50) - 1][((*data)->x_p / 50)] != '1')
	{
		(*data)->y_p -= 50;
		counter(&data);
	}
	if ((*data)->map[((*data)->y_p / 50)][((*data)->x_p / 50)] == 'C')
		coins(&data);
	(*data)->img = mlx_xpm_file_to_image((*data)->mlx, \
	"./sprites/pac_open_left.xpm", &img_w, &img_h);
	mlx_put_image_to_window((*data)->mlx, (*data)->win, \
	(*data)->img, (*data)->x_p, (*data)->y_p);
}

void	mv_down(t_data **data)
{
	int		img_w;
	int		img_h;

	(*data)->img = mlx_xpm_file_to_image((*data)->mlx, \
	"./sprites/stolenfloor.xpm", &img_w, &img_h);
	mlx_put_image_to_window((*data)->mlx, (*data)->win, \
	(*data)->img, (*data)->x_p, (*data)->y_p);
	if ((*data)->map[((*data)->y_p / 50) + 1][((*data)->x_p / 50)] == 'E')
	{
		if ((*data)->collect <= 0)
			exit_door(&data);
	}
	else if ((*data)->map[((*data)->y_p / 50) + 1][((*data)->x_p / 50)] != '1')
	{
		(*data)->y_p += 50;
		counter(&data);
	}
	if ((*data)->map[((*data)->y_p / 50)][((*data)->x_p / 50)] == 'C')
		coins(&data);
	(*data)->img = mlx_xpm_file_to_image((*data)->mlx, \
	"./sprites/pac_open_left.xpm", &img_w, &img_h);
	mlx_put_image_to_window((*data)->mlx, (*data)->win, \
	(*data)->img, (*data)->x_p, (*data)->y_p);
}

void	mv_left(t_data **data)
{
	int		img_w;
	int		img_h;

	(*data)->img = mlx_xpm_file_to_image((*data)->mlx, \
	"./sprites/stolenfloor.xpm", &img_w, &img_h);
	mlx_put_image_to_window((*data)->mlx, (*data)->win, \
	(*data)->img, (*data)->x_p, (*data)->y_p);
	if ((*data)->map[((*data)->y_p / 50)][((*data)->x_p / 50 - 1)] == 'E')
	{
		if ((*data)->collect <= 0)
			exit_door(&data);
	}
	else if ((*data)->map[((*data)->y_p / 50)][((*data)->x_p / 50 - 1)] != '1')
	{
		(*data)->x_p -= 50;
		counter(&data);
	}
	if ((*data)->map[((*data)->y_p / 50)][((*data)->x_p / 50)] == 'C')
		coins(&data);
	(*data)->img = mlx_xpm_file_to_image((*data)->mlx, \
	"./sprites/pac_open_left.xpm", &img_w, &img_h);
	mlx_put_image_to_window((*data)->mlx, (*data)->win, \
	(*data)->img, (*data)->x_p, (*data)->y_p);
}

void	mv_right(t_data **data)
{
	int		img_w;
	int		img_h;

	(*data)->img = mlx_xpm_file_to_image((*data)->mlx, \
	"./sprites/stolenfloor.xpm", &img_w, &img_h);
	mlx_put_image_to_window((*data)->mlx, (*data)->win, \
	(*data)->img, (*data)->x_p, (*data)->y_p);
	if ((*data)->map[((*data)->y_p / 50)][((*data)->x_p / 50 + 1)] == 'E')
	{
		if ((*data)->collect <= 0)
			exit_door(&data);
	}
	else if ((*data)->map[((*data)->y_p / 50)][((*data)->x_p / 50 + 1)] != '1')
	{
		(*data)->x_p += 50;
		counter(&data);
	}
	if ((*data)->map[((*data)->y_p / 50)][((*data)->x_p / 50)] == 'C')
		coins(&data);
	(*data)->img = mlx_xpm_file_to_image((*data)->mlx, \
	"./sprites/pac_open_left.xpm", &img_w, &img_h);
	mlx_put_image_to_window((*data)->mlx, (*data)->win, \
	(*data)->img, (*data)->x_p, (*data)->y_p);
}
