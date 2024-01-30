/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:07:24 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/25 13:42:58 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	unsigned int	i;
	int				newword;
	char			c;

	i = 0;
	newword = 1;
	while (str[i] != '\0')
	{
		c = str[i];
		if (newword == 1 && c >= 'a' && c <= 'z')
		{
			str[i] = str[i] - 32;
		}
		else if (newword == 0 && c >= 'A' && c <= 'Z')
			str[i] += 32;
		if (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
			newword = 1;
		else
			newword = 0;
		i++;
	}
	return (str);
}
/*
#include <stdio.h>
int     main(void)
{
        char testString[] = "salut, com ? 42mots qte-dx; cite+et+un";

        printf("Original string: %s\n", testString);
        ft_strcapitalize(testString);
        printf("Capitalized string: %s\n", testString);
        return 0;
}
*/
