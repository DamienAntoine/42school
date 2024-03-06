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
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_printstr("(null)");
		return (6);
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
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
