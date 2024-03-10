void    create_lst(t_list **list, int fd)
{
    int     bytesread;
    char    *buf;

    while (!scanline(*list))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return ;
        char_read = read(fd, buf, BUFFER_SIZE);
        if (!bytesread)
        {
            free(buf);
            return ;
        }
        buf[bytesread] = '\0';
        lstcat(list, buf);
    }
}

char    *get_line(t_list *list)
{
    int     len;
    char    *nextstr;

    if (list == NULL)
        return (NULL);
    len = charcount(list);
    nextstr = malloc(len);
    if (nextstr == NULL)
        return (NULL);
    return (nextstr);
}



char    *get_next_line(int fd)
{
    static t_list   *list;
    char            *line;

    list = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
        return (NULL);
    create_lst(&list, fd);
    if (list == NULL)
        return (NULL);
    line = get_line(list);
    //copy the chars past newline, free used nodes
    return (line);
}