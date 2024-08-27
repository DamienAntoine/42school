#include "../headers/minishell.h"

// Function to find the value of the HOME environment variable in the linked list
char *find_env_value(t_env *env, const char *name) {
    while (env != NULL) 
    {
        if (!ft_strcmp(env->type, name)) 
            return (env->value);
        env = env->next;
    }
    return (NULL);  // Return NULL if the variable is not found
}

// Function to update or add an environment variable in the linked list
void update_env_value(t_env *env, const char *name, const char *new_value) 
{
    t_env   *new_env;

    while (env != NULL) 
    {
        if (!ft_strcmp(env->type, name)) 
        {
            free(env->value);  // Free the old value
            env->value = ft_strdup(new_value);  // Assign the new value
            return;
        }
        env = env->next;
    }
    // If the variable is not found, you might want to add it to the list
    // This part is optional based on your requirements

     // Optionally, add new environment variable if not found
    new_env = malloc(sizeof(t_env));
    if (!new_env) 
        return ;  // Handle memory allocation failure
    new_env->type = ft_strdup(name);
    new_env->value = ft_strdup(new_value);
    new_env->next = env;
    env = new_env;
}