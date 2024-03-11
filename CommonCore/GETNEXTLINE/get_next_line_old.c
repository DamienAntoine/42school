/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:33:16 by dantoine          #+#    #+#             */
/*   Updated: 2024/03/07 11:33:57 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_clearstash(char *stash)
{
	char	*temp;
	size_t	size;
	int		i;
	int		j;

	printf("\n\n-----------------\n");
	printf("\nentered clearstash\n");
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
	while (stash[i])
	{
		temp[j] = stash[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	printf("\nstash cleared\n");
	free(stash);
	printf("\nexited clearstash\n\n");
	printf("\n\n-----------------\n");
	return (temp);
}

char	*ft_readfile(int fd, char **buffer, char *stash)
{
	size_t	bytesread;

	printf("\n\n-----------------\n");
	printf("\nentered readfile\n");
	*buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (*buffer == NULL)
		return (NULL);
	(*buffer)[0] = '\0';
	while (ft_scanline(stash) != 0)
	{
		printf("\nstash content before strlcat: %s\n", stash);
		bytesread = read(fd, *buffer, BUFFER_SIZE);
		printf("\nbuffer content: %s\n", *buffer);
		if (bytesread < 0)
		{
			printf("error");
			free(*buffer);
			return (NULL);
		}
		(*buffer)[bytesread] = '\0';
		ft_strlcat(stash, *buffer, ft_strlen(stash) + BUFFER_SIZE + 1);
		printf("\nstash content after strlcat: %s\n", stash);
	}
	printf("\nstash content after loop: %s\n", stash);
	free(*buffer);
	printf("\nexited readfile\n\n");
	printf("\n\n-----------------\n");
	return (stash);
}

void	get_line(char *stash, char *line)
{
	int	i;
	int	j;

	printf("\n\n-----------------\n");
	printf("\nentered getline\n");
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
	printf("\nexited getline\n\n");
	printf("\n\n-----------------\n");
}

void	ft_scancheck(char *stash, char **temp, char **line)
{
	size_t	len;

	printf("\n\n-----------------\n");
	printf("\nentered scancheck\n");
	printf("stash: %s, temp: %s, line: %s", stash, *temp, *line);
	if (ft_scanline(stash) == 1)
	{
		printf("entered if condition");
		len = ft_strlen(stash);
		get_line(stash, *line);
		*temp = ft_clearstash(stash);
		len = ft_strlen(*temp);
		*line = (char *)realloc(*line, len + 1);
		if (*temp != NULL && *line != NULL)
			ft_strlcat(*line, *temp, len + 1);
		free(*temp);
	}
	printf("\nexited scancheck\n\n");
	printf("\n\n-----------------\n");
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*buffer;
	char			*line;
	char			*temp;

	printf("\n-----------------\n");
	printf("\nstart\n");
	stash = (char *)malloc(BUFFER_SIZE + 1);
	line = (char *)malloc(1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
	{
		printf("errorgnl");
		free(line);
		free(stash);
		return (NULL);
	}
	buffer = NULL;
	stash = ft_readfile(fd, &buffer, stash);
	printf("\nreadfile done\n");
	ft_scancheck(stash, &temp, &line);
	printf("\nscancheck done\n");
	printf("\n\n-----------------\n");
	free(stash);
	return (line);
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
