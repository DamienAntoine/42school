#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	buffer;
	size_t bytesread;

	bytesread = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytesread == -1)
		error;
	else if (bytesread == 0)
		Endoffile;
	else
		buffer[bytesread] = '\0';
}