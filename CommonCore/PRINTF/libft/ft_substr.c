/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:17:47 by dantoine          #+#    #+#             */
/*   Updated: 2024/02/22 12:18:29 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;

	i = start - 1;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s[++i] != '\0' && len != 0)
	{
		new[j] = s[i];
		j++;
		len--;
	}
	new[j] = '\0';
	return (new);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str;
	size_t	len;
	char *new;

	str = "test string 123456";
	len = ft_strlen(str);

	if (new)
	{
		new = ft_substr(str, 12, 6);
		printf("Original: %s\n", str);
		printf("New: %s", new);
	}
	else
		printf("Failed");
	return (0);
}
*/
