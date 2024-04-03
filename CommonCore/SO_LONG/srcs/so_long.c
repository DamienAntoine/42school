#include "../headers/so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;
	if (argc < 2)
	{
		perror("ERROR");
		return (1);
	}
	data.win_w = 1920;
	data.win_h = 1080;
	data.mlx = mlx_init();

	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, data.win_w, data.win_h, "SO_LONG");
	if (!data.win)
		return (1);

	mlx_loop(data.mlx);
	return (0);
}