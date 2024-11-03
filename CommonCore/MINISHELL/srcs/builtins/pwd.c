/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:10:11 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:10:12 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_env *cur_env)
{
	while (ft_strcmp(cur_env->type, "PWD") != 0)
		cur_env = cur_env->next;
	ft_putstr_fd(cur_env->value, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
