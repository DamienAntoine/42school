#include "../../headers/minishell.h"
//syntax: cd <path>
//should work with relative path (from current directory) and
//also with absolute path (from home directory)

static char *get_current_directory() 
{
    return (getcwd(NULL, 0));  // Get the current working directory
}

void ft_cd(t_command *current)
{
    char *home;
    char *oldpwd;
    char *newpwd;

    oldpwd = get_current_directory();  
    if (!oldpwd) 
    {
        perror("getcwd");
        return;
    }

    home = find_env_value(current->env, "HOME");
    
    if (current->args[1]) 
    {
        printf_and_free("Too many args for cd command\n", oldpwd);
        return;
    }

    if (!current->args[0]) 
    {  // No arguments, move to home directory
        if (!home) {
            printf_and_free("Home directory not set\n", oldpwd);
            return;
        }
        if (chdir(home) != 0) {  // Moving to home directory
            perror_and_free("cd", oldpwd);
            return;
        }
    } else if (!ft_strcmp(current->args[0], "..")) 
    {  // Argument is "..", move one directory up
        if (chdir("..") != 0) {  // Moving one directory up
            perror_and_free("cd", oldpwd);
            return;
        }
    } else if (!ft_strcmp(current->args[0], "-")) 
    {  // Argument is "-", move to previous directory
        char *oldpwd_env = find_env_value(current->env, "OLDPWD");
        if (!oldpwd_env) {
            printf_and_free("OLDPWD not set\n", oldpwd);
            return;
        }
        if (chdir(oldpwd_env) != 0) 
        {  // Moving to previous directory
            perror_and_free("cd", oldpwd);
            return;
        } 
        else
            printf("%s\n", oldpwd_env);  // Print the directory after changing to it
    } 
    else 
    {  // Move to the specified directory
        if (chdir(current->args[0]) != 0) {  // Moving to the specified directory
            perror_and_free("cd", oldpwd);
            return;
        }
    }

    // If we moved successfully, update OLDPWD and PWD
    update_env_variable(current->env, "OLDPWD", oldpwd);
    
    newpwd = get_current_directory();  // Get the new current directory
    if (!newpwd) 
    {
        perror_and_free("getcwd", oldpwd);
        return;
    }

    update_env_variable(current->env, "PWD", newpwd);

    free(oldpwd);  // Free the old PWD
    free(newpwd);  // Free the new PWD string allocated by get_current_directory()
}
