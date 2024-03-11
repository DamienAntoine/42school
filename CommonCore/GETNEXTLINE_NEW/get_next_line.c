#include "get_next_line.h"

void    create_lst(t_list **list, int fd)
{
    int     bytesread;
    char    *buf;

    while (!scanline(*list))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return ;
        bytesread = read(fd, buf, BUFFER_SIZE);
        if (!bytesread)
        {
            free(buf);
            return ;
        }
        buf[bytesread] = '\0';
        ft_lstcat(list, buf);
        free(buf);
    }
}

int scanline(t_list *list)
{
    t_list  *current;
    char    *str;
    current = list;
    while (current != NULL)
    {
        str = current->str_buf;
        if (ft_strchr(str, '\n') != NULL)
        {
            return (1);
        }
        current = current->next;
    }
    return (0);
}

char    *get_next_line(int fd)
{
    static t_list   *list;
    char            *line;
    int             len;

//    list = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    create_lst(&list, fd);
    if (list == NULL)
        return (NULL);
    len = charcount(list);
    line = malloc(len + 1);
    if (line == NULL)
        return (NULL);
    lst_strcat(list, line);
    //copy the chars past newline, free used nodes
    return (line);
}