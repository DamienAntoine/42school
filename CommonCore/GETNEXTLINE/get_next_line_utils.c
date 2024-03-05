#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

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

int	ft_scanline(char *str)
{
	printf("\nentered ft_scanline\n");
	if (str && *str != '\0')
	{
		while (str && *str != '\0')
		{
			if (*str == '\n')
				return (1);
			str++;
		}
		printf("\nnewline found in ft_scanline\n");
		printf("\n\n-----------------\n");
		return (0);
	}
	printf("\nexited scanline without finding newline\n\n");
	return (1);
}