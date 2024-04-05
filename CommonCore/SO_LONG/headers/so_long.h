#ifndef SO_LONG_H
# define SO_LONG_H

# include "../includes/get_next_line/get_next_line.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_data {
    void    *mlx;
	void	*img;
    void    *win;
    int     win_w;
    int     win_h;
    int     x_p;
    int     y_p;
    int     mvmt;
    char    **map;
    int     collect;
}		t_data;

size_t	ft_strlen(const char *str);
int		map_height(char **map);

#endif
