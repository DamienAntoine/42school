/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:19:47 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/14 17:21:21 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str != '\0')
	{
		if ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z'))
			str++;
		else
			return (0);
	}	
	return (1);
}
/*#include <stdio.h>

int main(void)
{
    char str[] = "aAaaaAAA1";
    int result = ft_str_is_alpha(str);

    if (result)
    {
        printf("The string is alpha\n");
    }
    else
    {
        printf("The string is not purely alpha.\n");
    }

    return 0;
}*/
