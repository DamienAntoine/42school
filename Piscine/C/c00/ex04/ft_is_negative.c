/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:05:51 by dantoine          #+#    #+#             */
/*   Updated: 2024/01/11 10:52:29 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_is_negative(int n)
{
	char	output;

	if (n >= 0)
	{
		output = 'P';
		write(1, &output, 1);
	}
	else
	{
		output = 'N';
		write(1, &output, 1);
	}
}
