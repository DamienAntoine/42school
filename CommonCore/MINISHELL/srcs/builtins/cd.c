#include "../../headers/minishell.h"

char	*get_current_directory(void)
{
	return (getcwd(NULL, 0));
}

int	ft_cd(t_data *cur)
{
	char	*target_dir;
	char	*oldpwd;
	char	*newpwd;
	char	*oldpwd_env;

	target_dir = NULL;
	oldpwd = get_current_directory();
	if (!oldpwd)
	{
		perror("getcwd");
		return (1);
	}
	if (cur->commands->args[1])
	{
		errno = EINVAL;
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		free(oldpwd);
		cur->state.last_exit_status = 1;
		return (1);
	}
	if (!cur->commands->args[0])
	{
		target_dir = find_env_value(cur->env, "HOME");
		if (!target_dir)
		{
			printf_and_free("Home directory not set\n", oldpwd);
			cur->state.last_exit_status = 1;
			return (1);
		}
	}
	else if (!ft_strcmp(cur->commands->args[0], ".."))
		target_dir = "..";
	else if (!ft_strcmp(cur->commands->args[0], "-"))
	{
		oldpwd_env = find_env_value(cur->env, "OLDPWD");
		if (!oldpwd_env || ft_strlen(oldpwd_env) == 0)
		{
			printf_and_free("OLDPWD not set\n", oldpwd);
			cur->state.last_exit_status = 1;
			return (1);
		}
		printf("%s\n", oldpwd_env);
		target_dir = oldpwd_env;
	}
	else if (cur->commands->args[0][0] == '$')
	{
		target_dir = find_env_value(cur->env, &cur->commands->args[0][1]);
		if (!target_dir)
		{
			printf("cd: %s: No such environment variable\n",
				&cur->commands->args[0][1]);
			free(oldpwd);
			cur->state.last_exit_status = 1;
			return (1);
		}
	}
	else
		target_dir = cur->commands->args[0];
	if (chdir(target_dir) != 0)
	{
		perror_and_free("cd", oldpwd);
		cur->state.last_exit_status = 1;
		return (1);
	}
	newpwd = get_current_directory();
	if (!newpwd)
	{
		perror_and_free("getcwd", oldpwd);
		cur->state.last_exit_status = 1;
		return (1);
	}
	update_or_add_env_variable(&cur->env, "OLDPWD", oldpwd);
	update_or_add_env_variable(&cur->env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
