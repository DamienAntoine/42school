#include "../headers/fractol.h"

void	render_fractal(t_fractal_data *settings)
{
	if (strcmp(settings->type, "mandelbrot") == 0)
		render_mandelbrot(settings);
	else if (strcmp(settings->type, "julia") == 0)
	{
		if (settings->const_real == 0 && settings->const_imag == 0)
		{
			settings->const_real = -0.745429;
			settings->const_imag = 0.05;
		}
		render_julia(settings);
	}
	else if (strcmp(settings->type, "burningship") == 0)
		render_burningship(settings);
	else
	{
		ft_putstr("Supported fractals: mandelbrot, julia, burningship", 1);
		exit_program(settings);
	}
	mlx_put_image_to_window(settings->mlx, settings->win, settings->img, 0, 0);
}

void	setup_graphics(t_fractal_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_SIZE, WINDOW_SIZE, "FRACTOL");
	data->img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_size, &data->endian);
}

void	initialize_fractal(t_fractal_data *data, const char *type, char **argv)
{
	data->pos_x = 0;
	data->pos_y = 0;
	data->color_code = 0xFCBE11;
	data->zoom_level = 300;
	data->offset_x = -1.4;
	data->offset_y = -1.2;
	data->max_iters = 50;
	data->type = strdup(type);
	if (strcmp(type, "julia") == 0)
	{
		data->const_real = atof(argv[2]);
		data->const_imag = atof(argv[3]);
	}
}

int	main(int argc, char **argv)
{
	t_fractal_data	*data;

	if ((argc != 2 && argc != 4) || (strcmp(argv[1], "julia") == 0
			&& argc != 4))
	{
		ft_putstr("Usage: ./fractol <fractal> [<const_real> <const_imag>]", 1);
		ft_putstr("Available fractals: mandelbrot, julia, burningship", 1);
		return (0);
	}
	data = malloc(sizeof(t_fractal_data));
	initialize_fractal(data, argv[1], argv);
	setup_graphics(data);
	mlx_key_hook(data->win, handle_key, data);
	mlx_mouse_hook(data->win, handle_mouse, data);
	mlx_hook(data->win, 17, 0L, exit_program, data);
	render_fractal(data);
	mlx_loop(data->mlx);
	return (0);
}
