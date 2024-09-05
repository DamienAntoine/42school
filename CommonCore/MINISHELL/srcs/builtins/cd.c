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
	printf("Old PWD: %s\n", oldpwd);

	// Check if too many arguments are passed
	if (cur->commands->args[1])
	{
		printf_and_free("Too many args for cd command\n", oldpwd);
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
			return ;
		}
	}
	else if (!ft_strcmp(cur->commands->args[0], ".."))
	{
		target_dir = "..";
	}
	else if (!ft_strcmp(cur->commands->args[0], "-"))
	{
		oldpwd_env = find_env_value(cur->env, "OLDPWD");
		if (!oldpwd_env)
		{
			printf_and_free("OLDPWD not set\n", oldpwd);
			return ;
		}
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
			return;
		}
	}
	else
	{
		// Move to the specified directory
		target_dir = cur->commands->args[0];
	}

	// Perform the directory change
	if (chdir(target_dir) != 0)
	{
		perror_and_free("cd", oldpwd);
		return ;
	}

	// Get the new current directory
	newpwd = get_current_directory();
	if (!newpwd)
	{
		perror_and_free("getcwd", oldpwd);
		return ;
	}

	// Update OLDPWD and PWD environment variables
	update_env_variable(cur->env, "OLDPWD", oldpwd);
	update_env_variable(cur->env, "PWD", newpwd);

	// Debug: Print the new directory after changing
	printf("New PWD: %s\n", newpwd);

	// Clean up
	free(oldpwd);
	free(newpwd);
}

/*
void	ft_cd(t_data *cur)
{

	char	*home;
	char	*oldpwd;
	char	*newpwd;
	char	*oldpwd_env;
printf("before current dir\n");


	current = data->commands;
	oldpwd = get_current_directory();
	if (!oldpwd)
	{
		perror("getcwd");
		return ;
	}
printf("oldpwd = %s \n after current dir \n", oldpwd);

	home = find_env_value(cur->env, "HOME");
	
	printf("print env_ home : %s\n", home);
	
	if (cur->commands->args[1])
	{
		printf_and_free("Too many args for cd command\n", oldpwd);
		return ;
	}
	if (!cur->commands->args[0])
	{ // No arguments, move to home directory
		if (!home)
		{
			printf("home dir fail: %s\n", home);

			printf_and_free("Home directory not set\n", oldpwd);
			return ;
		}

		printf("home dir : %s\n", home);

		if (chdir(home) != 0)
		{ // Moving to home directory
			perror_and_free("cd", oldpwd);
			return ;
		}
	}
	

	else if (!ft_strcmp(cur->commands->args[0], ".."))
	{ // Argument is "..", move one directory up
		char	*cur_dir = get_current_directory();
		printf("current dir before cd .. : %s\n", cur_dir);
		free(cur_dir);
		
		
		if (chdir("..") != 0)
		{ // Moving one directory up
			perror_and_free("cd", oldpwd);
			return ;
		}

		cur_dir = get_current_directory();
		printf("after cd ..; %s\n", cur_dir);
		update_env_variable(cur->env, "PWD", cur_dir);
		free(cur_dir);

	}
	else if (!ft_strcmp(cur->commands->args[0], "-"))
	{ // Argument is "-", move to previous directory
		oldpwd_env = find_env_value(cur->env, "OLDPWD");
		if (!oldpwd_env)
		{
			printf_and_free("OLDPWD not set\n", oldpwd);
			return ;
		}
		if (chdir(oldpwd_env) != 0)
		{ // Moving to previous directory
			perror_and_free("cd", oldpwd);
			return ;
		}
		else
			printf("%s\n", oldpwd_env);
				// Print the directory after changing to it
	}
	else
	{ // Move to the specified directory
		if (chdir(cur->commands->args[0]) != 0)
		{ // Moving to the specified directory
			perror_and_free("cd", oldpwd);
			return ;
		}
	}
	// If we moved successfully, update OLDPWD and PWD
	update_env_variable(cur->env, "OLDPWD", oldpwd);
	newpwd = get_current_directory(); // Get the new current directory
	if (!newpwd)
	{
		perror_and_free("getcwd", oldpwd);
		return ;
	}
	update_env_variable(cur->env, "PWD", newpwd);
	free(oldpwd); // Free the old PWD
	free(newpwd);
		// Free the new PWD string allocated by get_current_directory()
}
*/
