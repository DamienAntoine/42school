void    populate_struct(int value)
{

}

void    *str_to_int(char *str)
{
    int i;

    i = 0;
    
    populate_struct(ft_atoi()
}

void    handle_arrays(char **str)
{
    int i;
    int res;
    char    *split_str;

    i = 0;
    while (str[i])
    {
        split_str = ft_strdup(str[i]);
        res = ft_atoi(split_str);
        populate_struct(res);
        free(split_str);
        i++;
    }
}

int main(int argc, char **argv)
{
    int    *astack;
    int    *bstack;
    int     i;
    int     j;

    if (argc < 2)
	    return (0);
    if (!check_input(argv))
	    exit_error(NULL, NULL);
    bstack = NULL;
    if (argc > 1)
    {
        i = 0;
        j = 0;
        while (argv[i])
        {
            while (argv[i][j])
            {
                if (argv[i][j] == ' ')
                {
                    handle_arrays(ft_split(argv[i], ' '));

                }
                else
                {
                    populate_struct(ft_atoi(argv[i]));
                }
                j++;
            }
            i++;
        }
    }
    
}
