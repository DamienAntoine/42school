#include "../../headers/minishell.h"

///// MUST handle  LLONG_MIN    LLONG_MAX too.


void set_exit_status(long status, t_data *data)
{
    long normalized_status;
    long modulo;

    if (status >= 0)
        normalized_status = status % 256;
    else
    {
        modulo = status % 256;
        normalized_status = 256 + modulo;
        if (modulo == 0)
            normalized_status = 0; // Handle cases where modulo is 0
    }
    data->state.last_exit_status = (int)normalized_status;
}


/* void update_exit_status(t_data *data, long long status)
{
    if (status < 0 || status > 255)
    {
        // Ensure the exit status is within the valid range of long long int
        status = 1; // Default to 1 on invalid status
    }
    data->state.last_exit_status = status;
}
 */
void	ft_exit(t_data *data)
{
	char *status_str = remove_balanced_quotes(data->commands->args[0]);
	int status = ft_atoi(status_str); //ft_strtol needed+++++++++

	if (data->commands->args[0] && !data->commands->args[1])
	{
		if (ft_isalpha(status_str[0]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			set_exit_status(2, data); // exit hello hardcode non numeric
		}
		else
			set_exit_status(status, data);
	}
	else if (data->commands->args[1])
	{
		if (ft_isdigit(status_str[0]))
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			set_exit_status(1, data);
		}

		else
		{
            ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
            set_exit_status(2, data); // Non-numeric first argument, exit with status 2
        }

	}
	else
		set_exit_status(data->state.last_exit_status, data);


	free_minishell(data);
	/*
	// Optionally print the exit status
	if (status != 0)
	{
		ft_putstr_fd("Exiting with status ", STDERR_FILENO);
		ft_putnbr_fd(status, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	set_exit_status(status, data);
	*/
	// Exit the shell process with the specified status
	exit(data->state.last_exit_status);
}