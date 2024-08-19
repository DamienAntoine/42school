#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char	*ft_strdup(const char *str)
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

//for now it only prints the prompt (MSL$>) and asks for an input, then prints the input back.
//need to store the input in a struct, check if its a correct input and cut it into tokens
int	main(int argc, char **argv)
{
	char *input;

	if (argc > 1)
		exit(0);

	while (1)
	{
		write(1, "MSL$> " , 6);

		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
		{
			printf("End of file reached\n");
			exit(0);
		}
		printf("Command: %s", input);
		free(input);
	}
	return (0);
}
