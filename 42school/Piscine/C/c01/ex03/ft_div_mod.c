/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:22:32 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/14 17:37:33 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a / b;
	*mod = a % b;
}
/*#include <stdio.h>
int main(void)
{
    int dividend = 10;
    int divisor = 3;
    int quotient, remainder;

    ft_div_mod(dividend, divisor, &quotient, &remainder);

    printf("Dividend: %d\n", dividend);
    printf("Divisor: %d\n", divisor);
    printf("Quotient: %d\n", quotient);
    printf("Remainder: %d\n", remainder);

    return 0;
}*/
