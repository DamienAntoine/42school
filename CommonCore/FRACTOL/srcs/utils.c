#include "../headers/fractol.h"

void	put_pixel_to_image(t_fractal_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->line_size + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	exit_program(t_fractal_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	free(data);
	exit(1);
	return (0);
}

void	modify_iterations(t_fractal_data *data, int key_code)
{
	if (key_code == P_KEY)
	{
		if (data->max_iters > 10)
			data->max_iters -= 10;
	}
	else if (key_code == O_KEY)
	{
		if (data->max_iters < 4000)
			data->max_iters += 10;
	}
}
