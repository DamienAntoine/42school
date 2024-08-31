#include "../../headers/minishell.h"

void	error_msg(char *cmd, char *msg)
{
    ft_putstr_fd("minishell: ", 2);   // Print shell name to stderr
    ft_putstr_fd(cmd, 2);             // Print the command that caused the error
    ft_putstr_fd(": ", 2);            // Print colon and space
    ft_putendl_fd(msg, 2);            // Print the error message followed by a newline
}