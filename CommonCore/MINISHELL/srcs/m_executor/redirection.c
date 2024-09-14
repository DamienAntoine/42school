#include "../../headers/minishell.h"

//Opens the file based on the type of redirection (input, output, append).
//Returns the file descriptor (fd) for that file.

int open_redirection(t_redirection *redir) 
{
    int fd;

    if (redir->type == 0) 
    {  // Input
        fd = open(redir->file, O_RDONLY);
    }
	else if (redir->type == 1) 
	{  // Output
        fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } 
	else if (redir->type == 2) 
	{  // Append
        fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } 
	else if (redir->type == 3) 
	{  
        fd = handle_here_doc(redir);
    }
//    else 
//    {
//        fprintf(stderr, "Invalid redirection type: %d\n", redir->type);
//        return -1;
//    }
	if (fd < 0)
    {
        perror("open");
    }
    return fd;
}


int handle_here_doc(t_redirection *redir)
{
    char *delimiter = redir->file;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return -1;
    }

    printf("heredoc> ");
    while ((nread = getline(&line, &len, stdin)) != -1)
    {
        // Remove newline character
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (strcmp(line, delimiter) == 0)
            break;

        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);
        printf("heredoc> ");
    }
    free(line);
    close(pipefd[1]); // Close write end after writing

    return pipefd[0]; // Return read end for dup2
}

/*
Loops through all the redirections in a linked list and 
applies them using dup2 to redirect stdin or stdout as needed.
This is the function you'll use in the child process of your 
send_command function before calling execve.
*/

void setup_redirection(t_redirection *redir)
{
    int fd_in = -1, fd_out = -1, fd_append = -1;
    t_redirection *current = redir;

    // Traverse the redirection list to find the last redirection for each type
    while (current)
    {
        if (current->type == 0 || current->type == 3)
            fd_in = open_redirection(current);
        else if (current->type == 1)
            fd_out = open_redirection(current);
        else if (current->type == 2)
            fd_append = open_redirection(current);
        current = current->next;
    }

    // Apply the last input redirection
    if (fd_in != -1)
    {
        if (dup2(fd_in, STDIN_FILENO) == -1)
            perror("dup2");
        close(fd_in);
    }

    // Apply the last output redirection (append takes precedence if present)
    if (fd_append != -1)
    {
        if (dup2(fd_append, STDOUT_FILENO) == -1)
            perror("dup2");
        close(fd_append);
    }
    else if (fd_out != -1)
    {
        if (dup2(fd_out, STDOUT_FILENO) == -1)
            perror("dup2");
        close(fd_out);
    }
}

/*Adds a new redirection to your t_redirection linked list.
You would call this function when parsing the command, 
adding any redirections (<, >, >>) as they appear.*/
void add_redirection(t_data *data, char *file, int type) 
{
    t_redirection *new_redir = malloc(sizeof(t_redirection));
	t_redirection *tmp;
    tmp = NULL;
    if (!new_redir) 
	{
        perror("Failed to allocate memory for new redirection");
        return;
    }
	new_redir->file = strdup(file);
    if (!new_redir->file) 
	{
        free(new_redir);
        perror("Failed to duplicate file string");
        return;
    }
	new_redir->type = type;
    new_redir->next = NULL;
	// If there are no redirections yet, add the new one as the first element.
    if (data->redirects == NULL)
        data->redirects = new_redir; 
	else 
	{
        // Otherwise, find the end of the list and append the new redirection.
        tmp = data->redirects;
        while (tmp->next != NULL) 
		{
            tmp = tmp->next;
        }
        tmp->next = new_redir;
    }
}


void ft_sortredirect(t_data *data, int *i) {
    t_token_list *toklist = data->toklist;
    int redirect_type = -1;

    if (ft_strcmp(toklist->tokens[*i], "<") == 0)
        redirect_type = 0; // Input
    else if (ft_strcmp(toklist->tokens[*i], ">") == 0)
        redirect_type = 1; // Output
    else if (ft_strcmp(toklist->tokens[*i], ">>") == 0)
        redirect_type = 2; // Append
    else if (ft_strcmp(toklist->tokens[*i], "<<") == 0)
        redirect_type = 3; // Here-doc

    // Process redirection if a valid type was found
    if (redirect_type != -1) 
	{
        (*i)++;
        if (*i < toklist->token_count)
            add_redirection(data, toklist->tokens[*i], redirect_type);
        else
            // Error handling: expected a filename after redirection operator
        	fprintf(stderr, "Syntax error: No file name after redirection operator.\n");
        (*i)++;
    }
}
