/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:55 by dantoine          #+#    #+#             */
/*   Updated: 2024/03/05 15:21:25 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

size_t	ft_strlenptr(char *str)
{
	size_t	nb;

	nb = 0;
	while (*str != '\0')
	{
		nb++;
		str++;
	}
	return (nb);
}

int	ptrlen(int temp)
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
	const char	*hexdigits;
	uintptr_t	value;
	size_t		ptrsize;
	char		*hexstr;
	size_t			i;

	hexdigits = "0123456789abcdef";
	hexstr = NULL;
	value = (uintptr_t)ptr;
	i = 0;
	ptrsize = ptrlen(value);
	hexstr = (char *)malloc(ptrsize + 4);
	while (i < ptrsize)
	{
		hexstr[ptrsize - i - 1] = hexdigits[value % 16];
		value /= 16;
		i++;
	}
	hexstr[i++] = 'x';
	hexstr[i++] = '0';
	hexstr[i] = '\0';
	return (hexstr);
}

int	ft_printvoid(uintptr_t *ptr)
{
	int		i;
	char	*hex;

	hex = ft_createstr((void *)ptr);
	if (!hex)
		return (-1);
	i = ft_strlenptr(hex);
	while (i > 0)
	{
		i--;
		ft_putchar(hex[i]);
	}
	i = ft_strlenptr(hex);
	free(hex);
	return (i);
}
/*
#include <stdio.h>
int	main()
{
	void *ptr = "-10";
	ft_printvoid(ptr);
	printf("\n%p", ptr);
	return 0;
}
*/
