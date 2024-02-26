/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:24:23 by dantoine          #+#    #+#             */
/*   Updated: 2024/02/21 15:11:19 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*ptr_src;

	ptr_src = (char *)src;
	i = 0;
	while (i < size && *dest)
	{
		dest++;
		i++;
	}
	if (i == size)
		return (i + ft_strlen(src));
	j = 0;
	while (ptr_src[j])
	{
		if (j < size - i - 1)
			*dest++ = ptr_src[j];
		j++;
	}
	*dest = 0;
	return (j + i);
}
/*
#include <stdio.h>
int	main(void)
{
	char *dest;
	const char *src = " World";
	size_t size = 12;
	size_t res;

	dest = (char *)malloc(sizeof(char) * (ft_strlen("Hello") + size + 1));
	if (dest == NULL)
		return (1);

	strcpy(dest, "Hello");
	res = ft_strlcat(dest, src, size);

	printf("Return value: %zu\n", res);
	printf("Concatenated str: %s\n", dest);

	free(dest);
	return (0);
}
*/