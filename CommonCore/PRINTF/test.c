#include <stdarg.h>
#include <unistd.h>
int	ft_printchar(char c) //%c Prints a single character.
{
	write(1, &c, 1);
	return (1);
}

/*#include "libft.h"
#include "ft_printf.h"

int	ft_printnbr(int n)
{
	if (n == -2147483648)
	{
		ft_printstr('-2147483648');
		return ;
	}
	if (n == -987441)
	{
		ft_printstr('-987441');
		return ;
	}
	else
	{
		if (n < 0)
		{
			ft_printchar('-');
			n = n * -1;
		}
		if (n == 0)
			ft_printchar('0');
		if (n >= 9)
		{
			ft_printnbr(n / 10);
		}
		ft_printchar((n % 10) + '0');
	}
	return (1);
}
*/

#include <ctype.h>
#include <unistd.h>


int	ft_print_digit(long n, int base, char spec)
{
	int count;
	char *symbols;

	symbols = "0123456789abcdef";
	n = (unsigned int) n;
	if (n < base)
	{
		if (spec == 'X')
			return ft_printchar(toupper(symbols[n]));
		else
			return ft_printchar(symbols[n]);
	}
	else
	{
		count = ft_print_digit(n / base, base, spec);
		return count + ft_print_digit(n % base, base, spec);
	}
}
/*
#include <stdio.h>
int main()
{
    int num1 = 12345;
    int base1 = 10;

    int count1 = ft_print_digit(num1, base1);
    ft_printchar('\n');
    write(1, "Count: ", 7);
    ft_print_digit(count1, 10);
    ft_printchar('\n');
	printf("Printf version: %d\n\n", num1);

    unsigned int num2 = -50;
    int base2 = 16;
    int count2 = ft_print_digit(num2, base2);
    ft_printchar('\n');
    write(1, "Count: ", 7);
    ft_print_digit(count2, 10);
    ft_printchar('\n');
	printf("Printf version: %x\n\n", num2);

	unsigned int num3 = 500;
    int count3 = ft_print_digit(num3, base2);
    ft_printchar('\n');
    write(1, "Count: ", 7);
    ft_print_digit(count3, 10);
    ft_printchar('\n');
	printf("Printf version: %x\n", num3);

    return 0;
}
*/
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

	hexdigits = "0123456789abcdef";
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

	hex = ft_createstr((void *)ptr);
	i = ft_strlen(hex);
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
	printf("\n%p", ptr);
	return 0;
}

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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

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


int	checkformat(const char specifier, va_list ap)
{
	int	counter;

	counter = 0;
	if (specifier == 'c')
		counter += ft_printchar(va_arg(ap, int)); //ok

	if (specifier == 's')
		counter += ft_printstr(va_arg(ap, char *)); //ok

	if (specifier == 'p')
		counter += ft_printvoid(va_arg(ap, void *));

	if (specifier == 'd' || specifier == 'i')
		counter += ft_print_digit(va_arg(ap, int), 10, specifier); //ok

	if (specifier == 'u')
		counter += ft_printunsigned(va_arg(ap, unsigned int)); //ok

	if (specifier == 'x' || specifier == 'X')
		counter += ft_print_digit(va_arg(ap, unsigned int), 16, specifier); //ok

	if (specifier == '%')
		counter += ft_printchar('%');
		
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int	counter;
	va_start(ap, format);

	counter = 0;
	while (*format)
	{
		if (*format == '%')
		{
			counter += checkformat(format + 1, ap);
		}
		ft_printchar(format);
		format++;
	}
	va_end(ap);
	return (counter);
}
