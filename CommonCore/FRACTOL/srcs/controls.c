#include "../headers/fractol.h"

void	apply_zoom(t_fractal_data *data, int x, int y, int direction)
{
	double	zoom_factor;

	zoom_factor = 1.50;
	if (direction == 1)
	{
		data->offset_x = (x / data->zoom_level + data->offset_x) - (x
				/ (data->zoom_level * zoom_factor));
		data->offset_y = (y / data->zoom_level + data->offset_y) - (y
				/ (data->zoom_level * zoom_factor));
		data->zoom_level *= zoom_factor;
	}
	else if (direction == -1)
	{
		data->offset_x = (x / data->zoom_level + data->offset_x) - (x
				/ (data->zoom_level / zoom_factor));
		data->offset_y = (y / data->zoom_level + data->offset_y) - (y
				/ (data->zoom_level / zoom_factor));
		data->zoom_level /= zoom_factor;
	}
}

int	handle_key(int key_code, t_fractal_data *data)
{
	if (key_code == ESC)
		exit(1);
	else if (key_code == L_ARR)
		data->offset_x -= 50 / data->zoom_level;
	else if (key_code == R_ARR)
		data->offset_x += 50 / data->zoom_level;
	else if (key_code == U_ARR)
		data->offset_y -= 50 / data->zoom_level;
	else if (key_code == D_ARR)
		data->offset_y += 50 / data->zoom_level;
	else if (key_code == RESET_KEY)
		initialize_fractal(data, data->type, NULL);
	else if (key_code == A_KEY)
		data->color_code += (255 * 255 * 255) / 100;
	else if (key_code == O_KEY || key_code == P_KEY)
		modify_iterations(data, key_code);
	render_fractal(data);
	return (0);
}

int	handle_mouse(int mouse_code, int x, int y, t_fractal_data *data)
{
	if (mouse_code == SCROLL_UP)
		apply_zoom(data, x, y, 1);
	else if (mouse_code == SCROLL_DOWN)
		apply_zoom(data, x, y, -1);
	render_fractal(data);
	return (0);
}
