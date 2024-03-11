#include "get_next_line.h"
#include <stdio.h>

/*
int	ft_scanstash(char *str)
{
	if (str && *str != '\0')
	{
		while (str && *str != '\0')
		{
			if (*str == '\n')
				return (1);
			str++;
		}
		return (0);
	}
	return (1);
}

char	*ft_readfile(int fd, char *buf, char *stash)
{
	size_t	bytesread;

	buf = (char *)malloc(BUFFER_SIZE);
	next_lineif (bytesread < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[bytesread] = '\0';
		ft_strlcat(stash, buf, ft_strlen(stash) + BUFFER_SIZE);
	}
	free(buf);
	printf("stash: %s", stash);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
	{
		free(line);
		free(stash);
		return (NULL);
	}
	stash = ft_readfile(fd, buffer, stash);
}
*/

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	size_t	bytesread;

	while (find_newline(stash) != 1)
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (read(fd, &buffer, BUFFER_SIZE) < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		else
		{
			stash = (char *)malloc(bytesread + 1);
			bytesread = read(fd, buffer, BUFFER_SIZE);
			buffer[bytesread] = '\0';
			ft_strlcat(stash, buffer, BUFFER_SIZE + 1);
			free(buffer);
		}
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &stash, 0) < 0)
		return (NULL);
	stash = read_file(fd, stash);
}

#include <fcntl.h>

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return 1;
	char *str = get_next_line(fd);
	if (str == NULL)
		printf("failed read");
	else
	{
		printf("%s", str);
		free(str);
	}
    return 0;
}