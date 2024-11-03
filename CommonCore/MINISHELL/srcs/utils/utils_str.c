/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:19:33 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:19:34 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_delimiter(char c, const char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	h = haystack;
	n = needle;
	if (*needle == '\0')
		return ((char *)haystack);
	if (*haystack == '\0')
		return (NULL);
	while (*h && *n && *h == *n)
	{
		h++;
		n++;
	}
	if (*n == '\0')
		return ((char *)haystack);
	return (ft_strstr(haystack + 1, needle));
}
