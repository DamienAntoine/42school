/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:11:11 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/24 16:13:04 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	render_fractal(t_fractal_data *settings)
{
	if (ft_strcmp(settings->type, "mandelbrot") == 0)
		render_mandelbrot(settings);
	else if (ft_strcmp(settings->type, "julia") == 0)
	{
		if (!settings->const_real && !settings->const_imag)
		{
			settings->const_real = -0.745429;
			settings->const_imag = 0.05;
		}
		render_julia(settings);
	}
	else if (ft_strcmp(settings->type, "burningship") == 0)
		render_burningship(settings);
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
	data->type = ft_strdup(type);
	if (ft_strcmp(type, "julia") == 0)
	{
		if (ft_isdigit(argv[2]) == 1 && ft_isdigit(argv[3]) == 1)
		{
			data->const_real = ft_atof(argv[2]);
			data->const_imag = ft_atof(argv[3]);
		}
		else
		{
			ft_putstr("Usage: ./fractol <fractal> [<const_real> <const_imag>]");
			exit(0);
		}
	}
}

int	main(int argc, char **argv)
{
	t_fractal_data	*data;

	if ((argc != 2 && argc != 4) || (ft_strcmp(argv[1], "julia") == 0
			&& argc != 4))
	{
		ft_putstr("Usage: ./fractol <fractal> [<const_real> <const_imag>]");
		ft_putstr("Available fractals: mandelbrot, julia, burningship");
		return (0);
	}
	data = malloc(sizeof(t_fractal_data));
	initialize_fractal(data, argv[1], argv);
	if (check_type(data) == 1)
		return (1);
	setup_graphics(data);
	mlx_key_hook(data->win, handle_key, data);
	mlx_mouse_hook(data->win, handle_mouse, data);
	mlx_hook(data->win, 17, 0L, exit_program, data);
	render_fractal(data);
	mlx_loop(data->mlx);
	return (0);
}
