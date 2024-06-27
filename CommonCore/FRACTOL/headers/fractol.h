/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:29:25 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/24 16:29:27 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WINDOW_SIZE 800
# define ESC 65307
# define L_ARR 65361
# define R_ARR 65363
# define U_ARR 65362
# define D_ARR 65364
# define A_KEY 97
# define Z_KEY 122
# define O_KEY 111
# define P_KEY 112
# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct s_fractal_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	double	pos_x;
	double	pos_y;
	double	color_code;
	double	zoom_level;
	double	offset_x;
	double	offset_y;
	double	const_real;
	double	const_imag;
	double	z_real;
	double	z_imag;
	double	c_real;
	double	c_imag;
	int		max_iters;
	char	*type;
	int		argc;
}			t_fractal_data;

void		initialize_fractal(t_fractal_data *data, const char *type,
				char **argv);
void		ft_putstr(char *s);
void		ft_putchar(char c);
int			ft_strcmp(const char *s1, char *s2);
char		*ft_strdup(const char *src);
int			ft_isdigit(char *arg);
void		*ft_memcpy(void *dst, const void *src, size_t n);
size_t		ft_strlen(const char *str);
double		ft_atof(char *str);
void		setup_graphics(t_fractal_data *data);
int			check_type(t_fractal_data *data);
void		render_burningship(t_fractal_data *data);
void		render_julia(t_fractal_data *data);
void		*render_mandelbrot(t_fractal_data *data);
void		render_fractal(t_fractal_data *settings);
void		draw_mandelbrot(t_fractal_data *data);
void		draw_julia(t_fractal_data *data);
void		draw_burningship(t_fractal_data *data);
void		put_pixel_to_image(t_fractal_data *data, int x, int y, int color);
int			exit_program(t_fractal_data *data);
void		apply_zoom(t_fractal_data *data, int x, int y, int direction);
int			handle_key(int key_code, t_fractal_data *data);
int			handle_mouse(int mouse_code, int x, int y, t_fractal_data *data);
void		modify_iterations(t_fractal_data *data, int key_code);

#endif
