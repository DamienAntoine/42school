#include "../../headers/minishell.h"

int	handle_is_directory(t_data *data, char *exec_target, struct stat path_stat)
{
	if (S_ISDIR(path_stat.st_mode))
	{
		if (exec_target[0] == '.' || exec_target[0] == '/')
		{
			ft_putstr_fd(exec_target, STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			data->error_occurred = 1;
			return (126);
		}
		else
		{
			ft_putstr_fd(exec_target, STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			data->error_occurred = 1;
			return (127);
		}
	}
	return (0);
}

int	handle_permission_denied(t_data *data, char *exec_target)
{
	if (access(exec_target, F_OK) == 0
		&& access(exec_target, R_OK) == -1
		&& access(exec_target, W_OK) == -1
		&& access(exec_target, X_OK) == -1)
	{
		ft_putstr_fd(exec_target, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		data->error_occurred = 1;
		return (126);
	}
	else if (access(exec_target, F_OK) == 0 && access(exec_target, X_OK) == -1)
	{
		ft_putstr_fd(exec_target, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->error_occurred = 1;
		return (127);
	}
	return (0);
}

int	handle_exec_permission(t_data *data, char *exec_target, struct stat path_stat)
{
	if (S_ISREG(path_stat.st_mode) && access(exec_target, X_OK) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd(exec_target, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			data->error_occurred = 1;
			return (126);
		}
	}
	return (0);
}

int	handle_exec_error_if_part(t_data *data, char *exec_target, struct stat path_stat)
{
	int result;

	result = handle_is_directory(data, exec_target, path_stat);
	if (result != 0)
		return result;

	result = handle_permission_denied(data, exec_target);
	if (result != 0)
		return result;

	result = handle_exec_permission(data, exec_target, path_stat);
	if (result != 0)
		return result;

	return (0);
}


int	handle_exec_error_else_part(t_data *data, char *exec_target)
{
	if (errno == ENOENT)
	{
		if (exec_target[0] == '.' || exec_target[0] == '/')
		{
			ft_putstr_fd(exec_target, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd(exec_target, STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		}
		data->error_occurred = 1;
		return (127);
	}
	ft_putstr_fd(exec_target, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	data->error_occurred = 1;
	return (127);
}
