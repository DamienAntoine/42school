/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:29:41 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/20 13:30:50 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	int				destend;

	i = 0;
	destend = 0;
	while (dest[destend] != '\0')
	{
		destend++;
	}
	while (src[i] != '\0' && i < nb)
	{
		dest[destend] = src[i];
		i++;
		destend++;
	}
	dest[destend] = '\0';
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	src[] = "test";
	char	dest[20] = "ok";

	ft_strncat(dest, src, 10);
	printf("src after : %s\n dest after : %s", src, dest);
	return (0);
}
*/
