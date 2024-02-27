/*#include "libft.h"
#include "ft_printf.h"*/
#include <unistd.h>

int	ft_printstr(char *s) //%s Prints a string.
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		write(1, s, 1);
		count++;
		s++;
	}
	return (count);
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
