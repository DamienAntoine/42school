#include "../headers/so_long.h"

void	counter(t_data ***data)
{
	int		img_w;
	int		img_h;
	char	*text;
	char	*number;

	number = ft_itoa(++(**data)->mvmt);
	text = ft_strjoin("Move: ", number);
	(**data)->img = mlx_xpm_file_to_image((**data)->mlx, "./sprites/wall.xpm", &img_w, &img_h);
	mlx_put_image_to_window((**data)->mlx, (**data)->win, (**data)->img, 0, 0);
	mlx_put_image_to_window((**data)->mlx, (**data)->win, (**data)->img, 50, 0);
	mlx_put_image_to_window((**data)->mlx, (**data)->win, (**data)->img, 50 * 2, 0);
	mlx_string_put((**data)->mlx, (**data)->win, 5, 10, 0xfffffff, text);
	ft_printf("%s\n", number);
	free(text);
	free(number);
}