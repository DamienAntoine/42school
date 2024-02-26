/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:07:13 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/24 15:21:46 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*create_str(int size, char **strs, char *sep)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (i < size)
	{
		len += str_len(strs[i]);
		i++;
	}
	len += str_len(sep) * (size - 1);
	if (size <= 0)
		len = 1;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (0);
	return (str);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	str = create_str(size, strs, sep);
	i = -1;
	k = 0;
	while (++i < size)
	{
		j = 0;
		while (strs[i][j])
		{
			str[k++] = strs[i][j];
			j++;
		}
		j = 0;
		while (sep[j] && i != size - 1)
		{
			str[k++] = sep[j];
			j++;
		}
	}
	str[k] = '\0';
	return (str);
}
/*
#include <stdio.h>
int main()
{
    char *strs[] = {"Hello", "world", "from", "ft_strjoin"};
    int size = 4;
    char *sep = " ";

    // ft_strjoin = concatenate strings with separator
    char *result = ft_strjoin(size, strs, sep);

    // check if result is not NULL before using it
    if (result != NULL)
    {
        // print concatenated string
        printf("Concatenated String: %s\n", result);

        free(result);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
*/
