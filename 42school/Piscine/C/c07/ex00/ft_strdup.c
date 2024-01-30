/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:57:20 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/22 17:29:20 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

char	*ft_strcpy(char *dest, char *src)

{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src [i];
		i++;
	}
	dest [i] = '\0';
	return (dest);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

char	*ft_strdup(char *src)
{
	char	*newstring;
	size_t	len;

	len = ft_strlen(src) + 1;
	newstring = (char *)malloc(len);
	if (newstring == 0)
		return (0);
	newstring = ft_strcpy(newstring, src);
	return (newstring);
}
/*
#include <stdio.h>
int	main(void)
{
	char*	ogstr;
	char*	dupstr;

	ogstr = "I dont like this exercise";
	dupstr = ft_strdup(ogstr);

	if (dupstr != 0)
	{
		printf("Original str : %s\n", ogstr);
		printf("Duplicated str : %s\n", dupstr);
		free(dupstr);
	}
	else
		printf("failed malloc\n");
	return (0);
}
*/
