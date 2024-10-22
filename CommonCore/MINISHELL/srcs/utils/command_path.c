#include "../../headers/minishell.h"

char	*create_full_path(const char *path, size_t len, const char *cmd)
{
	char	*full_path;

	full_path = malloc(len + ft_strlen(cmd) + 2);
	// Allocate memory for the full path
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path, len + 1);
	// Copy the current path into full_path
	ft_strlcat(full_path, "/", len + 2);
	// Add a '/' after the path
	ft_strlcat(full_path, cmd, len + ft_strlen(cmd) + 2);
	// Append the command to full_path
	return (full_path);
}

char	*get_command_path(const char *cmd)
{
	char	*path;
	char	*full_path;
	char	*next_colon;
	size_t	len;

	full_path = NULL;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	while (*path)
	{
		next_colon = ft_strchr(path, ':');
		if (!next_colon)
			next_colon = path + ft_strlen(path);
		len = next_colon - path;
		full_path = create_full_path(path, len, cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
		if (*next_colon)
			path = next_colon + 1;
		else
			path = next_colon;
	}
	return (NULL);
}
