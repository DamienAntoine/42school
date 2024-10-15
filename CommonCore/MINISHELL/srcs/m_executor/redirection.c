#include "../../headers/minishell.h"

// Function to open files based on redirection type
int open_redirection(t_redirection *redir)
{
    int fd = -1;

    // Determine the type of redirection using if-else statements
    if (redir->type == 0) // Input redirection
        fd = open(redir->file, O_RDONLY);
    else if (redir->type == 1) // Output redirection
        fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (redir->type == 2) // Append redirection
        fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (redir->type == 3) // Here-doc
        fd = handle_here_doc(redir);

    return fd;
}

// Function to handle here-doc redirection
int handle_here_doc(t_redirection *redir)
{
    char *delimiter = redir->file;
    char *line = NULL;
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return -1;
    }

    while (1)
    {
        line = readline("heredoc> "); // Prompt for input
        if (line == NULL) // Handle Ctrl+D
        {
            ft_putstr_fd("\n", STDERR_FILENO);
            break;
        }

        if (ft_strcmp(line, delimiter) == 0) // Stop on delimiter
        {
            free(line);
            break;
        }

        write(pipefd[1], line, ft_strlen(line)); // Write to pipe
        write(pipefd[1], "\n", 1); // Add newline
        free(line);
    }

    close(pipefd[1]); // Close the write end of the pipe
    return pipefd[0]; // Return the read end of the pipe
}

int setup_redirection(t_redirection *redir)
{
    int fd;

    while (redir)
    {
        if (redir->type == 0) // Input redirection
        {
            fd = open_redirection(redir);
            if (fd == -1) {
                // Set an error flag and continue to the next redirection
                redir->error_flag = 1;
                redir = redir->next;
                continue;
            }
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                close(fd);
                return -1; // Handle other dup2 errors if necessary
            }
            close(fd);
        }
        else if (redir->type == 1) // Output redirection
        {
            fd = open_redirection(redir);
            if (fd == -1)
                return -1;
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                close(fd);
                return -1;
            }
            close(fd);
        }
        else if (redir->type == 2) // Append redirection
        {
            fd = open_redirection(redir);
            if (fd == -1)
                return -1;
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                close(fd);
                return -1;
            }
            close(fd);
        }
        else if (redir->type == 3) // Here-doc
        {
            // Implement your here-doc logic here
            // If waiting for input, ensure that it works correctly
            handle_here_doc(redir);
        }
        redir = redir->next;
    }
    return 0;
}




void add_redirection(t_data *data, char *file, int type)
{
    t_redirection *new_redir = malloc(sizeof(t_redirection));
    if (!new_redir)
    {
        perror("Failed to allocate memory for new redirection");
        return;
    }

    new_redir->file = ft_strdup(file);
    if (!new_redir->file)
    {
        free(new_redir);
        perror("Failed to duplicate file string");
        return;
    }

    new_redir->type = type;
    new_redir->next = NULL;

    // Add to the linked list of redirections
    if (data->redirects == NULL)
        data->redirects = new_redir;
    else
    {
        t_redirection *tmp = data->redirects;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = new_redir;
    }
}

void ft_sortredirect(t_data *data, int *i)
{
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
