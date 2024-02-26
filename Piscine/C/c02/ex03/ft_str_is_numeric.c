/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:35 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/14 17:18:45 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_numeric(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
/*#include <stdio.h>

int main(void)
{
    char str[] = "a1";
    int result = ft_str_is_numeric(str);

    if (result)
    {
        printf("The string is numeric.\n");
    }
    else
    {
        printf("The string is not purely numeric.\n");
    }

    return 0;
}*/
