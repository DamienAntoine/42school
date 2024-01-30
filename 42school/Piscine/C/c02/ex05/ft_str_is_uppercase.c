/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:47:51 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/14 17:51:14 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_uppercase(char *str)
{
	while (*str != '\0')
	{
		if (*str < 'A' || *str > 'Z')
			return (0);
		str++;
	}
	return (1);
}
/*#include <stdio.h>

int main(void)
{
    char str[] = "AAAA";
    int result = ft_str_is_uppercase(str);

    if (result)
    {
        printf("The string is uppercase.\n");
    }
    else
    {
        printf("The string is not purely uppercase.\n");
    }

    return 0;
}*/
