#include "../../headers/minishell.h"

char	*create_full_path(const char *path, size_t len, const char *cmd)
{
	char	*full_path;

	full_path = malloc(len + ft_strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path, len + 1);
	ft_strlcat(full_path, "/", len + 2);
	ft_strlcat(full_path, cmd, len + ft_strlen(cmd) + 2);
	return (full_path);
}

char	*colon_helper(char *next_colon, char *path)
{
	if (*next_colon)
		path = next_colon + 1;
	else
		path = next_colon;
	return (path);
}

char	*get_command_path(const char *cmd)
{
	char	*path;
	char	*full_path;
	char	*next_colon;
	size_t	len;

	full_path = NULL;
	path = getenv("PATH");
	if (!path || *path == '\0')
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
		path = colon_helper(next_colon, path);
	}
	return (NULL);
}
