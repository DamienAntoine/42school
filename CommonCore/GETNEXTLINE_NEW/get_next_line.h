#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

void    ft_lstcat(t_list **list, char *buf);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char    *lst_strcat(t_list *lst, char *nextstr);
int charcount(t_list *lst);

typedef struct s_list
{
	char		*str_buf;
	struct s_list	*next;
}		t_list;
#endif