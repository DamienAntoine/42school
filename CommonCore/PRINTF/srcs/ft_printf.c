/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:13 by dantoine          #+#    #+#             */
/*   Updated: 2024/02/28 17:04:55 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	checkformat(const char specifier, va_list ap)
{
	int	counter;

	counter = 0;
	if (specifier == 'c')
		counter += ft_printchar(va_arg(ap, int));
	if (specifier == 's')
		counter += ft_printstr(va_arg(ap, char *));
	if (specifier == 'p')
		counter += ft_printvoid(va_arg(ap, void *));
	if (specifier == 'd' || specifier == 'i')
		counter += ft_print_digit(va_arg(ap, int), 10, specifier);
	if (specifier == 'u')
		counter += ft_printunsigned(va_arg(ap, unsigned int));
	if (specifier == 'x' || specifier == 'X')
		counter += ft_print_digit(va_arg(ap, unsigned int), 16, specifier);
	if (specifier == '%')
		counter += ft_printchar('%');
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		counter;

	va_start(ap, format);
	counter = 0;
	while (*format)
	{
		if (*format == '%')
		{
			counter += checkformat(*(++format), ap);
			format++;
		}
		ft_printchar(*format);
		format++;
	}
	va_end(ap);
	return (counter);
}
