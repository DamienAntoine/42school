/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:53:00 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/14 20:53:52 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_printable(char *str)
{
	while (*str != '\0')
	{
		if (*str < 32 || *str > 126)
			return (0);
		str++;
	}
	return (1);
}
/*#include <stdio.h>
int main(void)
{
    char str[] = "HelloWor~~~~~ld!";

    if (ft_str_is_printable(str))
    {
        printf("The string is printable.\n");
    }
    else
    {
        printf("The string contains non-printable characters.\n");
    }

    return 0;
}*/
