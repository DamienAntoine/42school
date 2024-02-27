//#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

static int	ft_strlen(char *str)
{
	int	nb;

	nb = 0;
	while (*str != '\0')
	{
		nb++;
		str++;
	}
	return (nb);
}

static char *ft_uitoa(unsigned int n)
{
    char *str;
    int size;
	unsigned int temp;

    size =  0;
    temp = n;
	if (temp == 0)
	{
		write(1, "0", 1);
	}
	while (temp !=  0)
	{
		temp /=  10;
        size++;
	}
    str = (char *)malloc(sizeof(char) * (size +  1));
    if (!str)
        return (NULL);
    str[size] = '\0';
    while (size--)
	{
        str[size] = '0' + n %  10;
        n /=  10;
    }

    return (str);
}

int ft_printunsigned(unsigned int nb)
{
    char *ustr;
	
	ustr = ft_uitoa(nb);
    if (ustr)
	{
        write(1, ustr, ft_strlen(ustr));
        free(ustr);
    }
    return  (1);
}
/*
int main()
{
    unsigned int test = 0;
    ft_printunsigned(test);
    printf("\n%u\n\n", test);

	test = UINT_MAX;
    ft_printunsigned(test);
    printf("\n%u\n\n", test);

	test = -50;
    ft_printunsigned(test);
    printf("\n%u\n\n", test);
    return  (0);
}
*/