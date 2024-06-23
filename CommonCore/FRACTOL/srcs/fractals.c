#include "../headers/fractol.h"

void	draw_burningship(t_fractal_data *data)
{
	int		iter;
	int		color;
	double	temp_real;

	data->type = "burningship";
	iter = 0;
	data->z_real = 0.0;
	data->z_imag = 0.0;
	data->c_real = (data->pos_x / data->zoom_level) + data->offset_x;
	data->c_imag = (data->pos_y / data->zoom_level) + data->offset_y;
	while (++iter < data->max_iters)
	{
		temp_real = data->z_real * data->z_real - data->z_imag * data->z_imag
			+ data->c_real;
		data->z_imag = fabs(2.0 * data->z_real * data->z_imag) + data->c_imag;
		data->z_real = fabs(temp_real);
		if (data->z_real * data->z_real + data->z_imag
			* data->z_imag >= __DBL_MAX__)
			break ;
	}
	if (iter == data->max_iters)
		color = 0x000000;
	else
		color = (data->color_code * iter);
	put_pixel_to_image(data, data->pos_x, data->pos_y, color);
}

void	draw_julia(t_fractal_data *data)
{
	int		iter;
	int		color;
	double	temp_real;

	data->type = "julia";
	data->z_real = data->pos_x / data->zoom_level + data->offset_x;
	data->z_imag = data->pos_y / data->zoom_level + data->offset_y;
	iter = 0;
	while (++iter < data->max_iters)
	{
		temp_real = data->z_real;
		data->z_real = data->z_real * data->z_real - data->z_imag * data->z_imag
			+ data->const_real;
		data->z_imag = 2 * data->z_imag * temp_real + data->const_imag;
		if (data->z_real * data->z_real + data->z_imag
			* data->z_imag >= __DBL_MAX__)
			break ;
	}
	if (iter == data->max_iters)
		color = 0x000000;
	else
		color = (data->color_code * iter);
	put_pixel_to_image(data, data->pos_x, data->pos_y, color);
}

void	draw_mandelbrot(t_fractal_data *data)
{
	int		iter;
	int		color;
	double	temp_real;

	data->type = "mandelbrot";
	iter = 0;
	data->z_real = 0.0;
	data->z_imag = 0.0;
	data->c_real = (data->pos_x / data->zoom_level) + data->offset_x;
	data->c_imag = (data->pos_y / data->zoom_level) + data->offset_y;
	while (++iter < data->max_iters)
	{
		temp_real = data->z_real * data->z_real - data->z_imag * data->z_imag
			+ data->c_real;
		data->z_imag = 2.0 * data->z_real * data->z_imag + data->c_imag;
		data->z_real = temp_real;
		if (data->z_real * data->z_real + data->z_imag
			* data->z_imag >= __DBL_MAX__)
			break ;
	}
	if (iter == data->max_iters)
		color = 0x000000;
	else
		color = (data->color_code * iter);
	put_pixel_to_image(data, data->pos_x, data->pos_y, color);
}
