/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:33:00 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/15 19:19:32 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			if (s1[i] > s2[i])
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int main()
{
    char str1[] = "abcd";
    char str2[] = "abcd";

    int result = ft_strcmp(str1, str2);
    
    if (result == 0)
        printf("Strings are equal.\n");
    else if (result < 0)
        printf("String 1 is less than String 2.\n");
    else
        printf("String 1 is greater than String 2.\n");

    return 0;
}
*/
