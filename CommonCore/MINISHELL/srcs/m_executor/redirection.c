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

    // Check if file opening was successful
    if (fd == -1 && redir->error_flag != 1)
	{
        perror("Failed to open file for redirection");
		redir->error_flag = 1;
	}

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
    int fd_in = -1, fd_out = -1, fd_append = -1;
    t_redirection *current = redir;
    int result = 0;

    while (current)
    {
        if (current->type == 0)
        {
            fd_in = open_redirection(current);
            if (fd_in == -1)
                return -1;
        }
        else if (current->type == 1)
        {
            fd_out = open_redirection(current);
            if (fd_out == -1)
                return -1;
        }
        else if (current->type == 2)
        {
            fd_append = open_redirection(current);
            if (fd_append == -1)
                return -1;
        }
        current = current->next;
    }
    if (fd_in != -1)
    {
        if (dup2(fd_in, STDIN_FILENO) == -1)
        {
            close(fd_in);
            return -1;
        }
        close(fd_in);
    }
    if (fd_append != -1)
    {
        if (dup2(fd_append, STDOUT_FILENO) == -1)
        {
            close(fd_append);
            return -1;
        }
        close(fd_append);
    }
    else if (fd_out != -1)
    {
        if (dup2(fd_out, STDOUT_FILENO) == -1)
        {
            close(fd_out);
            return -1;
        }
        close(fd_out);
    }
    return result;
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
