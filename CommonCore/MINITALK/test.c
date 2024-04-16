#include "headers/minitalk.h"
#include <stdio.h>

char	test(char c)
{
	char letter = 0;
    int i = 7;

    while(i >= 0)
    {
        if (c & (1 << i))
        {
            letter |= (1 << i);
        }
        i--;
    }
    return letter;
}

int	main()
{
	int i = 0;
	char	*str = "abcdefg";
	char	c;


	while(str[i])
	{
		c = test(str[i]);
		printf("%c", c);
		i++;
	}
	printf("\n");
	return (0);
}
