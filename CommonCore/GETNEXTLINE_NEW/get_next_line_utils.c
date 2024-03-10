void    lstcat(t_list **list, char *buf)
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

int charcount(*lst)
{
    int len;
    int i;

    len = 0;
    while(lst != '\0')
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