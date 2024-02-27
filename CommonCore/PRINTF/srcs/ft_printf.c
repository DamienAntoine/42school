#include "libft.h"
#include "ft_printf.h"

int	checkformat(const char specifier, va_list ap)
{
	int	counter;

	counter = 0;
	if (specifier == '%c')
	{
		counter += ft_printchar(va_arg(ap, char)); //ok
	}
	if (specifier == '%s')
	{
		counter += ft_printstr(va_arg(ap, char *)); //ok
	}
	if (specifier == '%p')
	{
		counter += ft_printvoid(va_arg(ap, void *));
	}
	if (specifier == '%d' || specifier == '%i')
	{
		counter += ft_printnbr(va_arg(ap, int));
	}
	if (specifier == '%u')
	{
		counter += ft_printunsigned(ap, unsigned int);
	}
	if (specifier == '%x' || specifier == '%X')
	{
		counter +=
	}
	if (specifier == '%%')
	{
		counter += ft_printchar('%');
	}
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int	counter;
	while (*format)
	{
		if (format == '%')
		{
			counter += checkformat(++format, ap);
		}
		format++;
	}
	va_start(ap, *format);

	va_end(ap);
	return (counter);
}