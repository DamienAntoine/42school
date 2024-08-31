#include "../../headers/minishell.h"



int is_delimiter(char c, const char *delimiter)
{
    int i;

    i = 0;
    while (delimiter[i])
    {
        if (delimiter[i] == c)
            return (1);
        i++;
    }
    return (0);
}


int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}
