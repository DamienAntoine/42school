/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:04:28 by dantoine          #+#    #+#             */
/*   Updated: 2024/05/02 14:04:48 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	put_image(t_data ***data, int x, int y, char *img)
{
	int		img_w;
	int		img_h;

	(**data)->img = mlx_xpm_file_to_image((**data)->mlx, img, &img_w, &img_h);
	mlx_put_image_to_window((**data)->mlx, (**data)->win, (**data)->img, x, y);
}

void	print_elem(char p, int x1, int y1, t_data **data)
{
	if (p == '1')
	{
		put_image(&data, x1, y1, "./sprites/stolenfloor.xpm");
		put_image(&data, x1, y1, "./sprites/tree.xpm");
	}
	else if (p == 'C')
	{
		put_image(&data, x1, y1, "./sprites/stolenfloor.xpm");
		put_image(&data, x1, y1, "./sprites/Egg.xpm");
		(*data)->collect++;
	}
	else if (p == 'E')
	{
		put_image(&data, x1, y1, "./sprites/stolenfloor.xpm");
		put_image(&data, x1, y1, "./sprites/pac_open_left.xpm");
	}
	else if (p == 'P')
	{
		(*data)->y_p = y1;
		(*data)->x_p = x1;
		put_image(&data, x1, y1, "./sprites/stolenfloor.xpm");
		put_image(&data, x1, y1, "./sprites/pac_open_left.xpm");
	}
	else
		put_image(&data, x1, y1, "./sprites/stolenfloor.xpm");
	free_images(*data);
}
