#include "../../headers/minishell.h"

char	*get_command_path(const char *cmd)
{
	char *path = getenv("PATH");
	//char *dir;
	char *full_path = NULL;
	char *next_colon;
	size_t len;

	if (!path)
		return (NULL);

	// Process each directory in PATH
	while (*path)
	{
		// Find the next colon in PATH (or the end of the string)
		next_colon = strchr(path, ':');
		if (!next_colon)
			next_colon = path + ft_strlen(path);

		// Calculate the directory length
		len = next_colon - path;

		// Allocate memory for the full path: dir + "/" + cmd + null terminator
		full_path = malloc(len + ft_strlen(cmd) + 2);
		if (!full_path)
			return (NULL);

		// Copy the directory part
		ft_strlcpy(full_path, path, len + 1);
		ft_strlcat(full_path, "/", len + 2);
		ft_strlcat(full_path, cmd, len + ft_strlen(cmd) + 2);

		// Check if the command is executable
		if (access(full_path, X_OK) == 0)
			return (full_path);

		free(full_path);
		full_path = NULL;

		// Move to the next directory in PATH
		path = *next_colon ? next_colon + 1 : next_colon;
	}
	return (NULL);
}

/*
char	*get_command_path(const char *cmd)
{
	char *path = getenv("PATH");
	char *full_path = NULL;
	char *dir;
	size_t len;

	if (!path)
		return (NULL);

	path = ft_strdup(path); // Duplicate PATH because strtok modifies the string
	dir = ft_strtok(path, ":");

	while (dir)
	{
		// Allocate memory for the full path: dir + "/" + cmd + null terminator
		len = ft_strlen(dir) + ft_strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path);
			return (NULL);
		}

		// Construct the full path
		ft_strlcpy(full_path, dir, len);
		ft_strlcat(full_path, "/", len);
		ft_strlcat(full_path, cmd, len);

		if (access(full_path, X_OK) == 0)
		{ // Check if the command is executable
			free(path);
			return (full_path);
		}

		free(full_path);
		full_path = NULL;
		dir = ft_strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}
*/