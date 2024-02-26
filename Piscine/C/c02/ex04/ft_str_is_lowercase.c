/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:23:33 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/15 12:11:30 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str != '\0')
	{
		if (*str < 'a' || *str > 'z')
			return (0);
		str++;
	}
	return (1);
}
/*
#include <stdio.h>

int main(void)
{
    char str[] = "aaaaaa";
    int result = ft_str_is_lowercase(str);

    if (result)
    {
        printf("The string is lowercase.\n");
    }
    else
    {
        printf("The string is not purely lowercase.\n");
    }

    return 0;
}*/
