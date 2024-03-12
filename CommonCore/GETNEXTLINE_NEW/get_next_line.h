#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char		*str_buf;
	struct s_list	*next;
}		t_list;

t_list	*ft_lstlast(t_list *lst);
int	charcount(t_list *list);
void	struct_strcpy(t_list *list, char *str);
int	scanline(t_list *list);
void	unmalloc(t_list **list, t_list *clean, char *buf);

#endif