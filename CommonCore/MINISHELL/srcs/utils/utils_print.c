#include "../../headers/minishell.h"

void perror_and_free(const char *message, void *ptr) 
{
    if (message)
        perror(message);  // Print the error message
    if (ptr) 
        free(ptr);  // Free the allocated memory
}

//  perror_and_free("cd", oldpwd);   usage like this

void printf_and_free(const char *message, void *ptr) 
{
    if (message)
        printf("%s", message);  // Print the message
    if (ptr)
        free(ptr);  // Free the allocated memory
}