/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:37:05 by dantoine          #+#    #+#             */
/*   Updated: 2024/02/28 16:57:51 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

static char	*ft_uitoa(unsigned int n)
{
	unsigned int	temp;
	char			*str;
	int				size;

	size = 0;
	temp = n;
	if (temp == 0)
		write(1, "0", 1);
	while (temp != 0)
	{
		temp /= 10;
		size++;
	}
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size--)
	{
		str[size] = '0' + n % 10;
		n /= 10;
	}
	return (str);
}

int	ft_printunsigned(unsigned int nb)
{
	char	*ustr;

	ustr = ft_uitoa(nb);
	if (ustr)
	{
		write(1, ustr, ft_strlen(ustr));
		free(ustr);
	}
	return (1);
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
