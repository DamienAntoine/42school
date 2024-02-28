/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:36:55 by dantoine          #+#    #+#             */
/*   Updated: 2024/02/28 17:04:58 by dantoine         ###   ########.fr       */
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
	const char	*hexdigits;
	uintptr_t	value;
	size_t		ptrsize;
	char		*hexstr;
	int			i;

	hexdigits = "0123456789abcdef";
	hexstr = NULL;
	value = (uintptr_t)ptr;
	i = 0;
	ptrsize = ptrlen((uintptr_t)ptr, value);
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
	int		i;
	char	*hex;

	hex = ft_createstr((void *)ptr);
	i = ft_strlenptr(hex);
	while (i >= 0)
	{
		ft_putchar(hex[i]);
		i--;
	}
	free(hex);
	return (1);
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
