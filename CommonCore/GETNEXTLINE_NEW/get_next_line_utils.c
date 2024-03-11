#include "get_next_line.h"

void    ft_lstcat(t_list **list, char *buf)
{
    t_list  *newnode;
    t_list  *lastnode;

    newnode = malloc(sizeof(t_list));
    lastnode = ft_lstlast(*list);
    if (newnode == NULL)
        return ;
    if (lastnode == NULL)
        *list = newnode;
    else
        lastnode->next = newnode;
    newnode->str_buf = buf;
    newnode->next = NULL;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (unsigned char)c)
		{
			return (ptr);
		}
		ptr++;
	}
	if (*ptr == '\0' && c == '\0')
	{
		return (ptr);
	}
	return (NULL);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*ptr_src;

	ptr_src = (char *)src;
	i = 0;
	while (i < size && *dest)
	{
		dest++;
		i++;
	}
	if (i == size)
		return (i + ft_strlen(src));
	j = 0;
	while (ptr_src[j])
	{
		if (j < size - i - 1)
			*dest++ = ptr_src[j];
		j++;
	}
	*dest = 0;
	return (j + i);
}

char    *lst_strcat(t_list *lst, char *nextstr)
{
    int i;
    size_t len;

    i = 0;
    while (nextstr[i])
    {
        i++;
    }
    while (lst && ft_strchr(lst->str_buf, '\n'))
    {
        len = ft_strlen(lst->str_buf);
        ft_strlcat(nextstr, lst->str_buf, len);
        lst = lst->next;
    }
    return (nextstr);
}

int charcount(t_list *lst)
{
    int len;
    int i;

    len = 0;
    while(lst != NULL)
    {
        i = 0;
        while (lst->str_buf[i])
        {
            if (lst->str_buf[i] != '\n')
            {
                ++len;
                return (len);
            }
            ++i;
            ++len;
        }
        lst = lst->next;
    }
    return (len);
}