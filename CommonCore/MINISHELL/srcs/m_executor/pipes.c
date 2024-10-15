#include "../../headers/minishell.h"

void handle_pipe(t_data *data, int num_commands)
{
    t_command *cmdtable = data->commands;
    int pipes[num_commands - 1][2]; // -1 because there's always one less pipe than commands
    pid_t pid;
    int i, j, status;

    // Create pipes
	i = 0;
    while (i < num_commands - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
		i++;
    }

    // Fork and execute each command in the pipeline
	i = 0;
	while (i < num_commands)
    {
        if ((pid = fork()) == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) // Child process
        {
            // Handle redirections first
            if (data->redirects != NULL)
            {
                if (setup_redirection(data->redirects) == -1)
                    exit(1);
            }

            // Set up pipes if there are no redirections for STDIN/STDOUT
            int input_redirected = 0, output_redirected = 0;
            t_redirection *redir = data->redirects;

            // Check if input or output redirection is present
            while (redir)
            {
                if (redir->type == 0) // Input redirection
                    input_redirected = 1;
                if (redir->type == 1 || redir->type == 2) // Output or Append redirection
                    output_redirected = 1;
                redir = redir->next;
            }

            // Only set up pipes if no redirection is set for input/output
            if (i > 0 && !input_redirected) // Not the first command, no input redirection
            {
                dup2(pipes[i - 1][0], STDIN_FILENO); // Input from previous pipe
            }

            if (i < num_commands - 1 && !output_redirected) // Not the last command, no output redirection
            {
                dup2(pipes[i][1], STDOUT_FILENO); // Output to next pipe
            }

            // Close all pipes except the ones used by the current process
			j = 0;
            while (j < num_commands - 1)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
				j++;
            }

            // Execute the command
            data->commands = cmdtable; // Set the current command
            int exec_status = send_command(data); // Capture the command's exit status
            free_minishell(data);
            exit(exec_status); // Exit with the command's exit status
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

    // Wait for all child processes to finish
	i = 0;
    while (i < num_commands)
    {
        wait(&status);
        if (WIFEXITED(status))
            data->state.last_exit_status = WEXITSTATUS(status);
		i++;
    }
}
