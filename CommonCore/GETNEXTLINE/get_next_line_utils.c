#include "get_next_line.h"
#include <stdio.h>

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

int	find_newline(char *stash)
{
	int	i;

	while (stash[i] != '\n' || stash[i] != '\0')
	{
		i++;
	}
	if (stash == '\n')
		return (1);
	else
		return (0);
}