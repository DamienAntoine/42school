#ifndef SO_LONG_H
# define SO_LONG_H

# include "../includes/get_next_line/get_next_line.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include "ft_printf.h"

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


typedef struct	s_map_data {
    int    c;
    int    p;
    int    e;
    int    y;
    int    x;
}		t_map_data;

char	**parse_map(char *map);
void    mv_up(t_data **data);
void	mv_down(t_data **data);
void	mv_left(t_data **data);
void	mv_right(t_data **data);
void	counter(t_data ***data);
void	print_elem(char p, int x1, int y1, t_data **data);
void    check_map(t_data *data);
void	check_elem(t_data **data);
void    clean_map(t_data ***data);
int		map_height(char **map);
void	check_file(char *line);
void	exit_door(t_data ***data);
void	put_image(t_data ***data, int x, int y, char *img);

#endif
