/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:48 by dantoine          #+#    #+#             */
/*   Updated: 2024/02/28 16:40:11 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_digit(long n, int base, char spec)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	n = (unsigned int) n;
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
