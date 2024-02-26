/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:20:37 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/16 14:12:15 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	findend;

	i = 0;
	findend = 0;
	while (dest[findend] != '\0')
	{
		findend++;
	}
	while (src[i] != '\0')
	{
		dest[findend] = src[i];
		findend++;
		i++;
	}
	dest[findend] = '\0';
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	srcmain[] = "abcdefg";
	char	destmain[20] = "hiklmn";

	printf("Src before : %s\nDest before : %s.\n", srcmain, destmain);

	ft_strcat(destmain, srcmain);
	printf("Src after : %s\nDest after : %s.\n", srcmain, destmain);
	return (0);
}*/
