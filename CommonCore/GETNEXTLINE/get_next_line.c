#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	buffer;
	size_t bytesread;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	while (fd
	bytesread = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytesread == -1)
		error;
	else if (bytesread == 0)
		Endoffile;
	else
		buffer[bytesread] = '\0';
}
