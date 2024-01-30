/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:11:31 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/20 10:50:48 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *tofind)
{
	int	i;
	int	j;

	i = 0;
	if (tofind[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == tofind[j] && tofind[j] != '\0')
		{
			j++;
		}
		if (tofind [j] == '\0')
			return (&str[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int main() {
    char str[] = "abcd";
    char tofind[] = "d";

    char *result = ft_strstr(str, tofind);

    if (result != NULL)
    {
        printf("Substring found at position: %ld\n", result - str);
        printf("Substring: %s\n", result);
    }
    else
    {
        printf("Substring not found\n");
    }

    return 0;
}
*/
