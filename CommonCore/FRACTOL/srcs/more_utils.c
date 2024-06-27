/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:11:40 by dantoine          #+#    #+#             */
/*   Updated: 2024/06/24 16:11:41 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*access_src;
	unsigned char	*edit_dst;

	i = 0;
	access_src = (unsigned char *)src;
	edit_dst = (unsigned char *)dst;
	while (i < n)
	{
		edit_dst[i] = access_src[i];
		i++;
	}
	return (dst);
}

double	ft_atof(char *str)
{
	int		i;
	int		sign;
	double	fraction;
	double	afterdec;
	double	beforedec;

	i = 0;
	sign = 1;
	fraction = 1;
	afterdec = 0;
	beforedec = 0;
	while (str[i] <= 32 || str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] != '.')
	{
		beforedec = beforedec * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		fraction = fraction / 10;
		afterdec = afterdec + (str[i] - '0') * fraction;
		i++;
	}
	return (sign * (beforedec + afterdec));
}
