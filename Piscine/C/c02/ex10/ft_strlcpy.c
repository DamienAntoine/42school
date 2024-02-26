/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:29:49 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/25 13:38:12 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (src[count])
		count++;
	if (size < 1)
		return (count);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (count);
}
/*
#include <stdio.h>

int main()
{
	char source[] = "This is the source string.";
	char destination[50];

	printf("Source string: %s\n", source);
	printf("Initial destination: %s\n", destination);

	unsigned int copied = ft_strlcpy(destination, source, sizeof(destination));

	printf("After ft_strlcpy, destination: %s\n", destination);
	printf("Number of characters copied: %u\n", copied);

	return 0;
}
*/
