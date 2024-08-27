#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

static char	*ft_strdup(const char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i])
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_next_line(int fd)
{
	int		i;
	int		bytesread;
	char	c;
	char	buf[BUFFER_SIZE + 1];
	char	*start;
	char	*end;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((bytesread = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
		{
			buf[i++] = c;
			break ;
		}
		if (i >= BUFFER_SIZE - 1)
			break ;
		buf[i++] = c;
	}
	if (bytesread <= 0 && i == 0)
		return (NULL);
	buf[i] = '\0';
	return (ft_strdup(buf));
}
