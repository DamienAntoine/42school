/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:37:01 by dantoine          #+#    #+#             */
/*   Updated: 2024/02/28 16:52:41 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printstr(char *s)
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
