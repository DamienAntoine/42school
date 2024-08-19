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





size_t ft_toklen(const char *str, const char *delim)
{
	size_t len = 0;
	int i;

	if (str == NULL || delim == NULL)
		return 0;
	while (str[len])
	{
		i = 0;
		while (delim[i])
		{
			if (str[len] == delim[i])
				return (len);
			i++;
		}
		len++;
	}
	return (len);
}

// strtok is like ft_split but it replaces delimiter characters with null characters,making every word of the string a token. It returns the next token everytime its called.
char	*ft_strtok(char *str, const char *delimiter)
{
	static char *last = NULL; // keeps track of next token
	char	*start;
	char	*end;

	if (str == NULL)
		str = last;
	if (str == NULL || *str == '\0')
		return (NULL);
	start = str;
	end = start + ft_toklen(start, delimiter);
	if (*end != '\0')
	{
		*end = '\0';
		last = end + 1; // set the last pointer to the start of the next token
	}
	else
		last = NULL;
	return (start);
}

// for now it only prints the prompt (MSL$>) and asks for an input, then prints the input back.
// need to store the input in a struct, check if its a correct input and cut it into tokens (separate the command and the arguments)

int	main(int argc, char **argv)
{
	char	*input;

	if (argc > 1)
		exit(0);
	while (1)
	{
		write(1, "MSL$> ", 6);
		input = get_next_line(STDIN_FILENO); // alias for '1' in unistd.h
		if (input == NULL)
		{
			printf("End of file reached\n");
			exit(0);
		}
		printf("Command: %s", ft_strtok(input, " ")); // replace this with whatever it needs to process the commands
		free(input);
	}
	return (0);
}
