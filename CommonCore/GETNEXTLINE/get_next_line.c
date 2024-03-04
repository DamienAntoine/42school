#include "get_next_line.h"

char	*ft_clearstash(char *stash)
{
	char	*temp;
	size_t	size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
	{
		i++;
	}
	size = ft_strlen(stash);
	temp = (char *)malloc((size - i) + 1);
	if (temp == NULL)
		return (NULL);
	/*while (stash[i])
	{
		temp[j] = stash[i];
		j++;
		i++;
	}*/
	temp[j] = '\0';
	free(stash);
	return (temp);
}

void	ft_readfile(int fd, char **buffer, char *stash)
{
	size_t	bytesread;

	*buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (*buffer == NULL)
		return ;
	(*buffer)[0] = '\0';
	while (!ft_scanline(stash))
	{
		bytesread = read(fd, *buffer, BUFFER_SIZE);
		if (bytesread == 0)
		{
			free(*buffer);
			return ;
		}
		(*buffer)[bytesread] = '\0';
		ft_strlcat(stash, *buffer, BUFFER_SIZE);
	}
	free(*buffer);
}

void	get_line(char *stash, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[j])
	{
		j++;
	}
	while (stash[i] != '\n' && stash[i] != '\0')
	{
		line[j] = stash[i];
		i++;
		j++;
	}
	line[j] = '\0';
}

void	ft_scancheck(char *stash, char **temp, char **line)
{
	size_t	len;

	if (ft_scanline(stash) == 1)
	{
		len = ft_strlen(stash);
		get_line(stash, *line);
		*temp = ft_clearstash(stash);
		len = ft_strlen(*temp);
		*line = (char *)realloc(*line, len + 1);
		if (*temp != NULL && *line != NULL)
			ft_strlcat(*line, *temp, len + 1);
		free(*temp);
	}
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*buffer;
	char			*line;
	char			*temp;
	size_t			len;

	stash = NULL;
	stash = (char *)malloc(BUFFER_SIZE + 1);
	line = (char *)malloc(1);
	line[0] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
	{
		free(line);
		free(stash);
		return (NULL);
	}
	buffer = NULL;
	ft_readfile(fd, &buffer, stash);
	ft_scancheck(stash, &temp, &line);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
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
	str = get_next_line(fd);
	if (str == NULL)
		printf("failed read");
    close(fd);
    return 0;
}
