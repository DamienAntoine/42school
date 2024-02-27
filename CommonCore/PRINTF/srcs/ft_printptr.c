//#include "libft.h"
//#include "ft_printf.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
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

int	ptrlen(uintptr_t ptr, int temp)
{
	int	i;

	i = 0;
	while (temp)
	{
        temp /= 16;
        i++;
    }
	return (i);
}

char	*ft_createstr(void *ptr)
{
	int	i;
	const char* hexdigits;
	char *hexstr;
	uintptr_t value;
	size_t ptrsize;

	hexdigits = "0123456789ABCDEF";
	hexstr = NULL;
	value = (uintptr_t)ptr;
	i = 0;
	uintptr_t temp = value;
	ptrsize = ptrlen((uintptr_t)ptr, temp);
    hexstr = (char *)malloc(ptrsize + 3);
	while (value)
	{
		hexstr[i++] = hexdigits[value % 16];
		value /= 16;
	}
	hexstr[i++] = 'x';
	hexstr[i++] = '0';
	hexstr[i] = '\0';
	return (hexstr);
}

int	ft_printvoid(uintptr_t *ptr)
{
	int	i;
	char *hex;

	i = ft_strlen(hex);
	hex = ft_createstr((void *)ptr);
	while (i >= 0)
	{
		ft_putchar(hex[i]);
		i--;
	}
	free(hex);
	return (1);
}
#include <stdio.h>
int	main()
{
	void *ptr = "sdgdhfdshg";
	ft_printvoid(ptr);
	printf("%p", ptr);
	return 0;
}