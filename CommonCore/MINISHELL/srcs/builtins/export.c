
#include "../../headers/minishell.h"

//syntax: export
//implemented with no options

/*displays a list of all environment variables that have been
marked for export to child processes initiated by the current shell session*/

/*Displaying Exported Variables:
Running export without any arguments lists
all the variables that have been exported,
meaning they are available to child processes.
This is useful for verifying which environment
variables have been configured for export.*/

//to undo export, do unset.

// Function to insert a node into a sorted linked list
static void sorted_insert(t_env **sorted_list, t_env *new_node) {
    if (!(*sorted_list) || strcmp((*sorted_list)->type, new_node->type) >= 0) {
        new_node->next = *sorted_list;
        *sorted_list = new_node;
    } else {
        t_env *current = *sorted_list;
        while (current->next && strcmp(current->next->type, new_node->type) < 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Function to clone nodes for sorting to avoid modifying the original list
static t_env *clone_node(t_env *node) {
    if (node == NULL) return NULL;
    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node) return NULL;
    new_node->type = node->type;  // Assuming these are pointers and don't need duplication
    new_node->value = node->value;
    new_node->next = NULL;
    return new_node;
}

void print_export(t_env *env_list, t_state *state) {
    t_env *current = env_list;
    t_env *sorted_list = NULL;
    t_env *new_node;

    // Create a new sorted list
    while (current) {
        new_node = clone_node(current);
        if (new_node) {
            sorted_insert(&sorted_list, new_node);
        }
        current = current->next;
    }

    // Print the sorted list
    current = sorted_list;
    while (current) {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(current->type, 1);
        if (current->value && *current->value) {
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(current->value, 1);
            ft_putstr_fd("\"", 1);
        }
        ft_putchar_fd('\n', 1);
        current = current->next;
    }

    // Free the sorted list
    while (sorted_list) {
        current = sorted_list;
        sorted_list = sorted_list->next;
        free(current);  // Free the cloned node
    }
    state->last_exit_status = 0;
}

static void export_with_arg(t_env **env_list, char *arg, t_state *state)
{   
    char *name = ft_strtok(arg, "=");
    char *new_value = ft_strtok(NULL, "");

    if (new_value == NULL)
        new_value = "";  // Ensure new_value is not NULL

    // Find the end of the list or the existing variable to update
    t_env **current = env_list;
    while (*current && ft_strcmp((*current)->type, name) != 0) {
        current = &(*current)->next;
    }

    if (*current) 
    {
        // Update existing variable
        free((*current)->value);
        (*current)->value = ft_strdup(new_value);
        if ((*current)->value == NULL) {
            perror("Memory allocation failed for value");
            state->last_exit_status = 1;  // Indicate failure
            return;
        }
        state->last_exit_status = 0;  // Indicate success
    } 
    else 
    {
        // Append new variable at the end
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node) {
            perror("Failed to allocate memory for new environment variable");
            state->last_exit_status = 1;  // Indicate failure
            return;
        }
        new_node->type = ft_strdup(name);
        new_node->value = ft_strdup(new_value);
        new_node->next = NULL;

        if (new_node->type == NULL || new_node->value == NULL) {
            free(new_node->type);  // Clean up in case of partial failure
            free(new_node->value);
            free(new_node);
            state->last_exit_status = 1;  // Indicate failure
            return;
        }

        *current = new_node;  // Append the new node at the end of the list
        state->last_exit_status = 0;  // Indicate success
    }
}
/*
static void export_with_arg(t_env **env_list, char *arg)
{   
    char    *name = ft_strtok(arg, "=");
    char    *new_value = ft_strtok(NULL, "");

    if (new_value == NULL)
        new_value = "";  // Ensure new_value is not NULL

    // Find the end of the list or the existing variable to update
    t_env **current = env_list;
    while (*current && ft_strcmp((*current)->type, name) != 0) {
        current = &(*current)->next;
    }

    if (*current) {
        // Update existing variable
        free((*current)->value);
        (*current)->value = ft_strdup(new_value);
    } else {
        // Append new variable at the end
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node) {
            perror("Failed to allocate memory for new environment variable");
            return;
        }
        new_node->type = ft_strdup(name);
        new_node->value = ft_strdup(new_value);
        new_node->next = NULL;

        *current = new_node;  // Append the new node at the end of the list
    }
}
*/


void    handle_export(t_env **lst, char **args, t_state *state)
{
    int i;
    i = 1;
    while (args[i])
        export_with_arg(lst, args[i++], state);
}
