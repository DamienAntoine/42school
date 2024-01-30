/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:37:18 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/15 19:19:14 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	{
		while (s1[i] != '\0' || s2[i] != '\0')
		{
			if (i < n)
			{
				if (s1[i] != s2[i])
				{
					if (s1[i] > s2[i])
						return (1);
					else
						return (-1);
				}
			}
			i++;
		}
	}
	return (0);
}
/*
#include <stdio.h>
int main()
{
    char str1[] = "abcdeg";
    char str2[] = "abcdef";

    int result = ft_strncmp(str1, str2, 4);

    if (result == 0)
        printf("Strings are equal.\n");
    else if (result < 0)
        printf("String 1 is less than String 2.\n");
    else
        printf("String 1 is greater than String 2.\n");

    return 0;
}
*/
