#include "../mlx/mlx.h"
/*
int main()
{
    void    *mlx;
    void    *img;
    void    *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 1920, 1080, "test");
    img = mlx_new_image(mlx, 1920, 1080);
    mlx_loop(mlx);
}
*/
/*
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
    t_data  img_data;

	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img_data.img = mlx_new_image(mlx, 1920, 1080);
    addr.addr = mlx_get_data_addr(img_data.img &img_data.bits_per_pixel, &img_data.line_length, &img_data.endian)

    mlx_loop(mlx);
}
*/
/*
#define WIDTH 800
#define HEIGHT 600

void draw_square(void *mlx, void *win)
{
    int x = 100;  // X-coordinate of the square's top-left corner
    int y = 100;  // Y-coordinate of the square's top-left corner
    int size = 200;  // Size of the square
    int i = x;

    // Draw horizontal lines
    while (i < x + size)
    {
        mlx_pixel_put(mlx, win, i, y, 0xFFFFFF); // White color
        mlx_pixel_put(mlx, win, i, y + size, 0xFFFFFF);
        i++;
    }

    // Draw vertical lines
    i = y;
    while (i < y + size)
    {
        mlx_pixel_put(mlx, win, x, i, 0xFFFFFF);
        mlx_pixel_put(mlx, win, x + size, i, 0xFFFFFF);
        i++;
    }
}

int main()
{
    void *mlx;
    void *win;

    // Initialize connection to the X server
    mlx = mlx_init();
    if (!mlx)
        return 1;

    // Create a new window
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "Simple Square");
    if (!win)
        return 1;

    // Draw the square
    draw_square(mlx, win);

    // Start the event loop (program will stay in this loop until the window is closed)
    mlx_loop(mlx);

    return 0;
}
*/
