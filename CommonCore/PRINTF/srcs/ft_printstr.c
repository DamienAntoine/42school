/*#include "libft.h"
#include "ft_printf.h"*/
#include <unistd.h>

int	ft_printstr(char *s) //%s Prints a string.
{
	if (!s)
		return (0);
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
	return (1);
}
/*
#include <stdio.h>
int main()
{
	char *str = "";
	ft_printstr(str);
	printf("\n%s\n", str);
	return (0);
}
*/