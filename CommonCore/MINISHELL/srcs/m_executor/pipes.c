#include "../../headers/minishell.h"

int output_redirection_exists(t_redirection *redirects)
{
    while (redirects)
    {
        if (redirects->type == 1 || redirects->type == 2) // Output redirection (1: >, 2: >>)
            return 1;
        redirects = redirects->next;
    }
    return 0;
}


int handle_pipes(t_data *data, t_command *cmdtable, int num_commands)
{
    int pipes[num_commands - 1][2];
    pid_t pid;
    int i = 0;
    int j;
    int status;
    int exit_code = 0;
    pid_t child_pids[num_commands];

    // create pipes
    while (i < num_commands - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return -1;
        }
        i++;
    }

    i = 0;
    // fork and execute each command
    while (i < num_commands)
    {
        if ((pid = fork()) == -1)
        {
            perror("fork");
            return -1;
        }

        if (pid == 0) // Child
        {
            if (cmdtable->redirects != NULL)
            {
                if (setup_redirection(cmdtable->redirects) == -1)
                    exit(1);
            }

            // setup pipes for next command
            if (i > 0) // if not the first command redirect input from the previous pipe
                dup2(pipes[i - 1][0], STDIN_FILENO);
            // if not the last command
            if (i < num_commands - 1 && !output_redirection_exists(cmdtable->redirects))
                dup2(pipes[i][1], STDOUT_FILENO);

            // close pipes in child
			j = 0;
            while (j < num_commands - 1)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
				j++;
            }

            // execute the command
            data->commands = cmdtable;
            exit_code = send_command(data);
            free_minishell(data);
            exit(exit_code);
        }
        else
            child_pids[i] = pid;
        cmdtable = cmdtable->next;
        i++;
    }
    // close pipes
	i = 0;
    while (i < num_commands - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
		i++;
    }

    // wait for every childprocesxs
	i = 0;
    while (i < num_commands)
    {
        if (waitpid(child_pids[i], &status, 0) == -1)
        {
            perror("waitpid");
            exit_code = 1;
        }
        if (WIFEXITED(status))
        {
            data->state.last_exit_status = WEXITSTATUS(status);
            if (WEXITSTATUS(status) != 0)
                exit_code = 1;
        }
		i++;
    }

    return exit_code;
}


