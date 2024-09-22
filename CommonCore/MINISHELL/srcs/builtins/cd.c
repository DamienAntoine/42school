#include "../../headers/minishell.h"

// syntax: cd <path>
// should work with relative path (from current directory) and
// also with absolute path (from home directory)

char	*get_current_directory(void)
{
	return (getcwd(NULL, 0)); // Get the current working directory
}

void	ft_cd(t_data *cur)
{
	char	*target_dir = NULL;
	char	*oldpwd = get_current_directory();
	char	*newpwd;
	char	*oldpwd_env;

	if (!oldpwd)
	{
		perror("getcwd");
		return ;
	}

	// Debug: Print the current directory before changing
	//printf("Old PWD: %s\n", oldpwd);

	// Check if too many arguments are passed
	if (cur->commands->args[1])
	{
		errno = EINVAL;
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		free(oldpwd);
		cur->state.last_exit_status = 1;
		return ;
	}

	// Determine the target directory
	if (!cur->commands->args[0])
	{
		// No arguments, move to home directory
		target_dir = find_env_value(cur->env, "HOME");
		if (!target_dir)
		{
			printf_and_free("Home directory not set\n", oldpwd);
			cur->state.last_exit_status = 1;
			return ;
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
			return ;
		}
		printf("%s\n", oldpwd_env);
		target_dir = oldpwd_env;
	}
	else if (cur->commands->args[0][0] == '$')
	{
		// Argument is an environment variable, retrieve its value
		target_dir = find_env_value(cur->env, &cur->commands->args[0][1]);
		if (!target_dir)
		{
			printf("cd: %s: No such environment variable\n", &cur->commands->args[0][1]);
			free(oldpwd);
			cur->state.last_exit_status = 1;
			return;
		}
	}
	else
		target_dir = cur->commands->args[0];
	// Perform the directory change
	if (chdir(target_dir) != 0)
	{
		perror_and_free("cd", oldpwd);
		cur->state.last_exit_status = 1;
		return ;
	}

	// Get the new current directory
	newpwd = get_current_directory();
	if (!newpwd)
	{
		perror_and_free("getcwd", oldpwd);
		cur->state.last_exit_status = 1;
		return ;
	}

	// Update OLDPWD and PWD environment variables
	update_or_add_env_variable(&cur->env, "OLDPWD", oldpwd);
	update_or_add_env_variable(&cur->env, "PWD", newpwd);

	// Debug: Print the new directory after changing
	//printf("New PWD: %s\n", newpwd);

	// Clean up
	free(oldpwd);
	free(newpwd);
}
