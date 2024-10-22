#include "../../headers/minishell.h"

char	*get_command_path(const char *cmd)
{
	char *path;
	char *full_path = NULL;
	char *next_colon;
	size_t len;

    path = getenv("PATH");
	if (!path)
		return (NULL);
	while (*path)
	{
		next_colon = ft_strchr(path, ':');
		if (!next_colon)
			next_colon = path + ft_strlen(path);
		len = next_colon - path;
		full_path = malloc(len + ft_strlen(cmd) + 2);
		if (!full_path)
			return (NULL);
		ft_strlcpy(full_path, path, len + 1);
		ft_strlcat(full_path, "/", len + 2);
		ft_strlcat(full_path, cmd, len + ft_strlen(cmd) + 2);
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
