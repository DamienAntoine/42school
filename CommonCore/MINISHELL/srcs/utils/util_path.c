/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:13:23 by dantoine          #+#    #+#             */
/*   Updated: 2024/11/03 12:13:23 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*is_direct_path(const char *cmd)
{
	if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*get_initial_command_path(t_data *data, const char *cmd, char **path)
{
	char	*direct_path;

	direct_path = is_direct_path(cmd);
	if (direct_path)
		return (direct_path);
	*path = find_env_value(data->env, "PATH");
	if (!*path || **path == '\0')
		return (NULL);
	return (NULL);
}

char	*get_command_path(t_data *data, const char *cmd)
{
	char	*path;
	char	*full_path;
	char	*next_colon;
	size_t	len;

	full_path = get_initial_command_path(data, cmd, &path);
	if (full_path)
		return (full_path);
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
		path = colon_helper(next_colon, path);
	}
	return (NULL);
}
