/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:17:11 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:17:11 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_current_directory(void)
{
	return (getcwd(NULL, 0));
}

int	handle_home_directory(t_data *cur, char **target_dir, char *oldpwd)
{
	*target_dir = find_env_value(cur->env, "HOME");
	if (!*target_dir)
	{
		printf_and_free("Home directory not set\n", oldpwd);
		return (1);
	}
	return (0);
}

int	handle_oldpwd(t_data *cur, char **target_dir, char *oldpwd)
{
	char	*oldpwd_env;

	oldpwd_env = find_env_value(cur->env, "OLDPWD");
	if (!oldpwd_env || ft_strlen(oldpwd_env) == 0)
	{
		printf_and_free("OLDPWD not set\n", oldpwd);
		return (1);
	}
	printf("%s\n", oldpwd_env);
	*target_dir = oldpwd_env;
	return (0);
}

int	handle_env_variable(t_data *cur, char **target_dir, char *oldpwd)
{
	*target_dir = find_env_value(cur->env, &cur->commands->args[0][1]);
	if (!*target_dir)
	{
		printf("cd: %s: No such environment variable\n",
			&cur->commands->args[0][1]);
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	validate_arguments(t_data *cur, char *oldpwd)
{
	if (cur->commands->args[1])
	{
		errno = EINVAL;
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		free(oldpwd);
		cur->state.last_exit_status = 1;
		return (1);
	}
	return (0);
}
