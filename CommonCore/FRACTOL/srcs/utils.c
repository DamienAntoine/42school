/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:11:24 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/24 16:11:25 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	put_pixel_to_image(t_fractal_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->line_size + x * (data->bits_per_pixel
				/ 8));
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

int	check_type(t_fractal_data *data)
{
	if (ft_strcmp(data->type, "mandelbrot") != 0 && ft_strcmp(data->type,
			"burningship") != 0 && ft_strcmp(data->type, "julia") != 0)
	{
		ft_putstr("Supported fractals: mandelbrot, julia, burningship");
		return (1);
	}
	else
		return (0);
}

int	ft_isdigit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] <= '9' && arg[i] >= '0') || arg[i] == '.')
			i++;
		else
			return (0);
	}
	return (1);
}
