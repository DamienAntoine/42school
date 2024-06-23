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
}
