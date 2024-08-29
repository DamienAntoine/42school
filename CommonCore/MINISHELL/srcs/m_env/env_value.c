#include "../../headers/minishell.h"

// Function to find the value of the HOME environment variable in the linked list
char *find_env_value(t_env *env, const char *name) 
{
    while (env != NULL) 
    {
        if (!ft_strcmp(env->type, name)) 
            return (env->value);
        env = env->next;
    }
    return (NULL);  // Return NULL if the variable is not found
}


void update_env_value(t_env **env, const char *name, const char *new_value) 
{
    t_env *current;
    t_env *prev;
    t_env   *new_env;

    current = *env;
    prev = NULL;
    // Traverse the list to find the variable or the end of the list
    while (current != NULL) {
        if (ft_strcmp(current->type, name)) {
            free(current->value);  // Free the old value
            current->value = strdup(new_value);  // Assign the new value
            return;
        }
        prev = current;
        current = current->next;
    }

    // Variable not found, so add a new one
    new_env = malloc(sizeof(t_env));
    if (!new_env) return;  // Handle memory allocation failure
    new_env->type = ft_strdup(name);
    new_env->value = ft_strdup(new_value);
    new_env->next = NULL;

    if (prev) {
        // Attach the new node to the end of the list
        prev->next = new_env;
    } else {
        // If the list was empty, set new_env as the head
        *env = new_env;
    }
}

