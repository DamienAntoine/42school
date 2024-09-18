#include "../../headers/minishell.h"

///// MUST handle  LLONG_MIN    LLONG_MAX too.

void update_exit_status(t_data *data, long long status)
{
    if (status < 0 || status > 255)
    {
        // Ensure the exit status is within the valid range of long long int
        status = 1; // Default to 1 on invalid status
    }
    data->state.last_exit_status = status;
}

void	ft_exit(t_data *data, int status)
{
	// Cleanup the environment
	if (data->env)
		free_env_list(data->env);

	// Cleanup commands and their components
	if (data->commands)
		free_command(data->commands);

	// Cleanup redirections (if separate from commands)
	// Note: This assumes redirections are not part of commands
	if (data->redirects)
		free_redirections(data->redirects);

	// Cleanup token list
	if (data->toklist)
		free_token_list(data->toklist);

	// Optionally print the exit status
	if (status != 0)
	{
		ft_putstr_fd("Exiting with status ", STDERR_FILENO);
		ft_putnbr_fd(status, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	update_exit_status(data, status);
	// Exit the shell process with the specified status
	exit(status);
}