/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:09:16 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/03 12:09:46 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	change_directory(t_data *cur, const char *target_dir, char *oldpwd)
{
	if (chdir(target_dir) != 0)
	{
		perror_and_free("cd", oldpwd);
		cur->state.last_exit_status = 1;
		return (1);
	}
	return (0);
}

static void	update_environment(t_data *cur, char *oldpwd, char *newpwd)
{
	up_env(&cur->env, "OLDPWD", oldpwd);
	up_env(&cur->env, "PWD", newpwd);
}

static char	*get_target_dir(t_data *cur, char *oldpwd)
{
	char	*target_dir;

	target_dir = NULL;
	if (!cur->commands->args[0])
	{
		if (handle_home_directory(cur, &target_dir, oldpwd))
			return (NULL);
	}
	else if (!ft_strcmp(cur->commands->args[0], ".."))
		target_dir = "..";
	else if (!ft_strcmp(cur->commands->args[0], "-"))
	{
		if (handle_oldpwd(cur, &target_dir, oldpwd))
			return (NULL);
	}
	else if (cur->commands->args[0][0] == '$')
	{
		if (handle_env_variable(cur, &target_dir, oldpwd))
			return (NULL);
	}
	else
		target_dir = cur->commands->args[0];
	return (target_dir);
}

int	ft_cd(t_data *cur)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target_dir;

	oldpwd = get_current_directory();
	if (!oldpwd)
	{
		perror("getcwd");
		return (1);
	}
	target_dir = get_target_dir(cur, oldpwd);
	if (validate_arguments(cur, oldpwd) || !target_dir)
		return (1);
	if (change_directory(cur, target_dir, oldpwd))
		return (1);
	newpwd = get_current_directory();
	if (!newpwd)
	{
		perror_and_free("getcwd", oldpwd);
		return (1);
	}
	update_environment(cur, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
