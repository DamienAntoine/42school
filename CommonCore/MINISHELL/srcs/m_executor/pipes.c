#include "../../headers/minishell.h"

/*OLD HANDLE_PIPE (works but crashes with too many pipes)
void	handle_pipe(t_data *data)
{
	t_command	*cmdtable;
	pid_t		pid;
	int			fd[2];
	int			previous_fd;

	previous_fd = -1; //signals first iteration (but gets reset everytime a forked process loops ?)
	// reset cmdtable to the start
	cmdtable = data->commands;

	while (cmdtable)
	{
		if (cmdtable->next)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();//create child
		if (pid == -1)//error value of fork
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // child
		{
			printf("child created with pid %d\n", getpid());
			if (previous_fd != -1)
			{
                printf("previous fd = -1 (pid: %d)\n", getpid());
				dup2(previous_fd, STDIN_FILENO);
				close(previous_fd);
			}
			if (cmdtable->next)
			{
				dup2(fd[1], STDOUT_FILENO);
			}
			close(fd[0]);
			close(fd[1]);
			data->commands = data->commands->next;
			execute_command(data);
			free_minishell(data);
			exit(0);
		}
		else // parent
		{
			if (cmdtable->next)
				close(fd[1]);
			if (previous_fd != -1)
				close(previous_fd);
			previous_fd = fd[0];
			cmdtable = cmdtable->next;
		}
	}
	while (wait(NULL) > 0)
		;
	if (previous_fd != -1)
		close(previous_fd);
}
*/

//NEWER HANDLE_PIPE (almost works but some errors with valgrind and doesnt execute the commands)
void	handle_pipe(t_data *data, pid_t parentpid)
{
	t_command	*cmdtable;
	pid_t		pid;
	int			fd[2];
	int			previous_fd;
    static int  counter; //debug

	previous_fd = -1; //signals first iteration (but gets reset everytime a forked process loops ?)
	// reset cmdtable to the start
	cmdtable = data->commands;
    pid = getpid();
	while (cmdtable)
	{
        counter++;
        printf("%d\n", counter);
		if (cmdtable->next)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
		}
        printf("process %d creates fork\n", getpid());
		pid = fork();//create child
		if (pid == -1)//error value of fork
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // child
		{
			printf("child created with pid %d\n", getpid());
            if (previous_fd == -1)
                printf("previous fd = -1 (pid: %d)\n", getpid());
			if (previous_fd != -1)
			{
				dup2(previous_fd, STDIN_FILENO);
				close(previous_fd);
			}
			if (cmdtable->next)
			{
				dup2(fd[1], STDOUT_FILENO);
			}
			close(fd[0]);
			close(fd[1]);
			data->commands = cmdtable->next;
			execute_command(data, parentpid);
			free_minishell(data);
			exit(0);
		}
		else // parent
		{
			if (cmdtable->next)
				close(fd[1]);
			if (previous_fd != -1)
				close(previous_fd);
			previous_fd = fd[0];
			cmdtable = cmdtable->next;
		}
	}
	while (wait(NULL) > 0)
		;
	if (previous_fd != -1)
		close(previous_fd);
}

//newest version: doesnt seem to leak but crashes when trying to execute cmd
/*void handle_pipe(t_data *data, pid_t parentpid)
{
    t_command *cmdtable;
    pid_t pid;
    int fd[2];
    int previous_fd = -1;
    static int counter;

    cmdtable = data->commands;

    while (cmdtable && cmdtable->next)
    {
        counter++;
        printf("%d\n", counter);

        // Reset previous_fd at the start of each iteration
        previous_fd = -1;

        // Create a pipe only if this is not the first command
        if (cmdtable != data->commands)
        {
            if (pipe(fd) == -1)
            {
                perror("pipe error");
                continue; // Skip to next command
            }
        }

        printf("process %d creates fork\n", getpid());
        pid = fork();

        if (pid == -1)
        {
            perror("fork error");
            continue; // Skip to next command
        }

        if (pid == 0) // child
        {
            printf("child created with pid %d\n", getpid());
            
            if (previous_fd != -1)
            {
                if (dup2(previous_fd, STDIN_FILENO) == -1)
                {
                    perror("dup2 stdin error");
                    exit(EXIT_FAILURE);
                }
                close(previous_fd);
            }

            if (cmdtable->next)
            {
                if (dup2(fd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 stdout error");
                    exit(EXIT_FAILURE);
                }
                close(fd[0]);
                close(fd[1]);
            }
            
            data->commands = cmdtable->next;
            execute_command(data, parentpid);
            free_minishell(data);
            exit(0);
        }
        else // parent
        {
            if (cmdtable->next && cmdtable != data->commands)
            {
                if (close(fd[0]) == -1 || close(fd[1]) == -1)
                {
                    perror("close error");
                    continue; // Skip to next command
                }
            }

            if (previous_fd != -1)
            {
                if (close(previous_fd) == -1)
                {
                    perror("close previous_fd error");
                    continue; // Skip to next command
                }
            }

            previous_fd = fd[0];
            cmdtable = cmdtable->next;
        }
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0)
        ;

    if (previous_fd != -1)
    {
        if (close(previous_fd) == -1)
        {
            perror("close final previous_fd error");
        }
    }
}*/

