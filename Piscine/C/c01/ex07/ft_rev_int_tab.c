/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:34:41 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/25 15:24:49 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_rev_int_tab(int *tab, int size)
{
	int	i;
	int	element;

	i = 0;
	while (i < size / 2)
	{
		element = tab[i];
		tab[i] = tab[size - i - 1];
		tab[size - i - 1] = element;
		i++;
	}
}
/*
#include <stdio.h>

int main()
{
    int size = 5;
    int tab[] = {1, 2, 3, 4, 5};

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    ft_rev_int_tab(tab, size);

    printf("Reversed array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    return 0;
}
*/
