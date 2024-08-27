#include "../../headers/minishell.h"
//syntax: cd <path>
//should work with relative path (from current directory) and
//also with absolute path (from home directory)
void    cd(t_command *current)
{
    char    *home = 
    if (current->args[1])
    {
        printf("Too many args for cd command");
        return ;
    }
    if (!current->args[0])
        //move to home
    else if (!ft_strcmp(current->args[0], ".."))
        // move one up
    else (current->args[0])
        // move to this path(current->args[i])
}

// NOT DONE AT ALL YET+ 
/*

    if (!current->args[0]) {  // No arguments, move to home directory
        const char *home = getenv("HOME");
        if (!home) {
            printf("Home directory not set\n");
            return;
        }
        if (chdir(home) != 0) {  // Moving to home directory
            perror("cd");
        }
    } else if (!strcmp(current->args[0], "..")) {  // Argument is "..", move one directory up
        if (chdir("..") != 0) {  // Moving one directory up
            perror("cd");
        }
    } else if (!strcmp(current->args[0], "-")) {  // Argument is "-", move to previous directory
        const char *oldpwd = getenv("OLDPWD");
        if (!oldpwd) {
            printf("OLDPWD not set\n");
            return;
        }
        if (chdir(oldpwd) != 0) {  // Moving to previous directory
            perror("cd");
        } else {
            printf("%s\n", oldpwd);  // Print the directory after changing to it
        }
    } else {  // Move to the specified directory
        if (chdir(current->args[0]) != 0) {  // Moving to the specified directory
            perror("cd");
        }
    }
}
*/

/*
chdir() Function:
Purpose: chdir() is a system call in C that changes the current working directory of the calling process.
Syntax: int chdir(const char *path);
path: The directory path to which you want to change.
Returns 0 on success, and -1 on failure (with errno set appropriately).
Moving Logic:
The actual "moving" is done by the chdir() function, which changes the directory based on the conditions defined in your function. Each call to chdir() attempts to change the current directory to a new one, whether it's the home directory, the parent directory, the previous directory, or a specified path.

*/