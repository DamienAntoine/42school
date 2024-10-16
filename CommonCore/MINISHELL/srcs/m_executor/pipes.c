#include "../../headers/minishell.h"

int handle_pipes(t_data *data, t_command *cmdtable, int num_commands)
{
    int pipes[num_commands - 1][2]; // -1 because there's always one less pipe than commands
    pid_t pid;
    int i = 0;
    int j;
    int status;
    int exit_code = 0;
    pid_t child_pids[num_commands]; // Array to store child PIDs for waitpid

    // Create pipes
    while (i < num_commands - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return -1; // Indicate pipe creation failure
        }
        i++;
    }

    i = 0;
    // Fork and execute each command in the pipeline
    while (i < num_commands)
    {
        if ((pid = fork()) == -1)
        {
            perror("fork");
            return -1; // Indicate fork failure
        }

        if (pid == 0) // Child process
        {
            if (data->redirects != NULL)
            {
                if (setup_redirection(data->redirects) == -1 && data->error_occurred != 1)
                    exit(1); // Exit the child process with an error
            }

            // Setup pipes
            if (i > 0) // If it's not the first command, redirect input from the previous pipe
                dup2(pipes[i - 1][0], STDIN_FILENO);
            if (i < num_commands - 1) // If it's not the last command, redirect output to the next pipe
                dup2(pipes[i][1], STDOUT_FILENO);

            // Close all pipes in the child process
            j = 0;
            while (j < num_commands - 1)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }

            // Execute the command
            data->commands = cmdtable; // Set the current command
            exit_code = send_command(data); // Capture exit code from send_command
            free_minishell(data);
            exit(exit_code); // Exit with the command's exit status
        }
        else
        {
            child_pids[i] = pid; // Store child PID for waitpid
        }

        cmdtable = cmdtable->next; // Move to the next command
        i++;
    }

    // Close all pipes in the parent process
    i = 0;
    while (i < num_commands - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }

    // Wait for each child process to finish in order, ensuring synchronization
    i = 0;
    while (i < num_commands)
    {
        // Use waitpid to wait for the exact child process
        if (waitpid(child_pids[i], &status, 0) == -1)
        {
            perror("waitpid");
            exit_code = 1; // Handle error in waitpid
        }
        if (WIFEXITED(status))
        {
            data->state.last_exit_status = WEXITSTATUS(status); // Store the exit status of the last command
            if (WEXITSTATUS(status) != 0)
                exit_code = 1; // If any command failed, set exit_code to 1
        }
        i++;
    }

    return exit_code; // Return the exit code for the last command
}
