/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:48 by dantoine          #+#    #+#             */
/*   Updated: 2024/03/04 15:38:01 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/ft_printf.h"
/*
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

int	ft_print_digit(long n, int base, char spec)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < 0)
	{
		ft_printchar('-');
		count++;
		n = -n;
	}
	if (n < base)
	{
		if (spec == 'X')
			return (ft_printchar(ft_toupper(symbols[n])));
		else
			return (ft_printchar(symbols[n]));
	}
	else
	{
		count = ft_print_digit(n / base, base, spec);
		return (count + ft_print_digit(n % base, base, spec));
	}
}
*/
int	ft_printnbr(int number)
{
	int	len;
	char	*str;

	len = 0;
	str = ft_itoa(number);
	len = ft_printstr(str);
	free(str);
	return (len);
}
/*
#include <stdio.h>
int main()
{
    int num1 = 12345;
    int base1 = 10;

    int count1 = ft_print_digit(num1, base1, 'd');
    ft_printchar('\n');
    write(1, "Count: ", 7);
    ft_print_digit(count1, 10, 'd');
    ft_printchar('\n');
	printf("Printf version: %d\n\n", num1);

    unsigned int num2 = -50;
    int base2 = 16;
    int count2 = ft_print_digit(num2, base2, 'x');
    ft_printchar('\n');
    write(1, "Count: ", 7);
    ft_print_digit(count2, 10, 'x');
    ft_printchar('\n');
	printf("Printf version: %x\n\n", num2);

	unsigned int num3 = 20000;
    int count3 = ft_print_digit(num3, base2, 'X');
    ft_printchar('\n');
    write(1, "Count: ", 7);
    ft_print_digit(count3, 10, 'X');
    ft_printchar('\n');
	printf("Printf version: %X\n", num3);

    return 0;
}
*/
