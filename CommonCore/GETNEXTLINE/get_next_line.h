#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 5

int	ft_scanline(char *line);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*get_next_line(int fd);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);

#endif