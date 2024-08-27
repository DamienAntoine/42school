#include "../../headers/minishell.h"
//syntax: cd <path>
//should work with relative path (from current directory) and
//also with absolute path (from home directory)

static char *get_current_directory() 
{
    char *buf;
    buf = NULL;
    buf = getcwd(NULL, 0);  // Get the current working directory
    return (buf);
}

void    cd(t_command *current)
{
    char    *home;
    char    *oldpwd;
    char    *newpwd;
     
    oldpwd = get_current_directory();  
    home = find_env_value(current->env, "HOME");
    if (current->args[1])
    {
        printf("Too many args for cd command");
        free(oldpwd);
        return ;
    }
    if (!current->args[0])
    {  // No arguments, move to home directory
        if (!home) {
            printf("Home directory not set\n");
            free(oldpwd);
            return;
        }
        if (chdir(home) != 0) {  // Moving to home directory
            perror("cd");
            free(oldpwd);
            return;
        }
    } else if (!strcmp(current->args[0], "..")) {  // Argument is "..", move one directory up
        if (chdir("..") != 0) {  // Moving one directory up
            perror("cd");
            free(oldpwd);
            return;
        }
    } else if (!strcmp(current->args[0], "-")) {  // Argument is "-", move to previous directory
        char *oldpwd_env = find_env_value(current->env, "OLDPWD");
        if (!oldpwd_env) {
            printf("OLDPWD not set\n");
            free(oldpwd);
            return;
        }
        if (chdir(oldpwd_env) != 0) {  // Moving to previous directory
            perror("cd");
            free(oldpwd);
            return;
        } else {
            printf("%s\n", oldpwd_env);  // Print the directory after changing to it
        }
    } else {  // Move to the specified directory
        if (chdir(current->args[0]) != 0) {  // Moving to the specified directory
            perror("cd");
            free(oldpwd);
            return;
        }
    }
    // If we moved successfully, update OLDPWD and PWD
    update_env_value(current->env, "OLDPWD", oldpwd);
    newpwd = get_current_directory();  // Get the new current directory
    update_env_value(current->env, "PWD", newpwd);

    free(oldpwd);  // Free the old PWD
    free(newpwd);  // Free the new PWD string allocated by get_current_directory()
}



    


/*
chdir() Function:
Purpose: chdir() is a system call in C that changes the current working directory of the calling process.
Syntax: int chdir(const char *path);
path: The directory path to which you want to change.
Returns 0 on success, and -1 on failure (with errno set appropriately).
Moving Logic:
The actual "moving" is done by the chdir() function, which changes the directory based on the conditions defined in your function. Each call to chdir() attempts to change the current directory to a new one, whether it's the home directory, the parent directory, the previous directory, or a specified path.

*/