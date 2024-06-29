/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_counter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:42:34 by dantoine          #+#    #+#             */
/*   Updated: 2024/05/02 15:42:35 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void counter(t_data ***data)
{
    int img_w;
    int img_h;
    char *text;
    char *number;

    number = ft_itoa(++(**data)->mvmt);
    if (!number)
	{
        exit(EXIT_FAILURE);
        return;
    }
    text = ft_strjoin("Move: ", number);
    if (!text)
	{
        free(number);
        exit(EXIT_FAILURE);
        return;
    }

    if ((**data)->img)
	{
        mlx_destroy_image((**data)->mlx, (**data)->img);
        (**data)->img = NULL;
    }

    (**data)->img = mlx_xpm_file_to_image((**data)->mlx, "./sprites/tree.xpm", &img_w, &img_h);
    if ((**data)->img)
	{
        mlx_put_image_to_window((**data)->mlx, (**data)->win, (**data)->img, 0, 0);
        mlx_put_image_to_window((**data)->mlx, (**data)->win, (**data)->img, 50, 0);
        mlx_put_image_to_window((**data)->mlx, (**data)->win, (**data)->img, 50 * 2, 0);
    }
	else
	{
        free_resources(**data);
		exit(EXIT_FAILURE);
    }

    mlx_string_put((**data)->mlx, (**data)->win, 5, 10, 0xffffff, text);
    ft_printf("%s\n", number);
    free(text);
    free(number);
}
