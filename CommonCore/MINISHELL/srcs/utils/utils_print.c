#include "../../headers/minishell.h"

void	perror_and_free(const char *message, void *ptr)
{
	if (message)
		perror(message);
	if (ptr)
		free(ptr);
}

void	printf_and_free(const char *message, void *ptr)
{
	if (message)
		printf("%s", message);
	if (ptr)
		free(ptr);
}