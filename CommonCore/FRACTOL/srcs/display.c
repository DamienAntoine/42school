/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:10:47 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/24 16:10:49 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	*render_mandelbrot(t_fractal_data *data)
{
	data->pos_x = 0;
	data->pos_y = 0;
	while (data->pos_x < WINDOW_SIZE)
	{
		while (data->pos_y < WINDOW_SIZE)
		{
			draw_mandelbrot(data);
			data->pos_y++;
		}
		data->pos_x++;
		data->pos_y = 0;
	}
    free(data->type);
	return (NULL);
}

void	render_julia(t_fractal_data *data)
{
	data->pos_x = 0;
	data->pos_y = 0;
	while (data->pos_x < WINDOW_SIZE)
	{
		while (data->pos_y < WINDOW_SIZE)
		{
			draw_julia(data);
			data->pos_y++;
		}
		data->pos_x++;
		data->pos_y = 0;
	}
    free(data->type);
}

void	render_burningship(t_fractal_data *data)
{
	data->pos_x = 0;
	data->pos_y = 0;
	while (data->pos_x < WINDOW_SIZE)
	{
		while (data->pos_y < WINDOW_SIZE)
		{
			draw_burningship(data);
			data->pos_y++;
		}
		data->pos_x++;
		data->pos_y = 0;
	}
    free(data->type);
}
