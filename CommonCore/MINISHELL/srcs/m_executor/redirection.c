#include "../../headers/minishell.h"

void handle_redirection(t_data *data) 
{
    t_redirection *redir = data->redirects;
    int fd;

    while (redir != NULL) 
	{
        if (redir->type == 0) 
		{  // Input
            fd = open(redir->file, O_RDONLY);
            if (fd == -1) 
			{
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
		else if (redir->type == 1) 
		{  // Output
            fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) 
			{
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } 
		else if (redir->type == 2) 
		{  // Append
            fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) 
			{
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } 
		else if (redir->type == 3) 
		{  // Here-doc
            // Here-doc logic needs to be implemented
        } 
		else 
		{
            fprintf(stderr, "Unknown redirection type\n");
            exit(EXIT_FAILURE);
        }
        redir = redir->next;  // Move to the next element in the list
    }
}

void add_redirection(t_data *data, char *file, int type) 
{
    t_redirection *new_redir = malloc(sizeof(t_redirection));
	t_redirection *tmp;
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

/*
t_redirection *ft_create_redirection(char *file, int type)
{
	t_redirection *redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(file);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

void ft_add_redirection(t_data *data, char *file, int type)
{
	t_redirection *redir;
    t_redirection *tmp;

	redir = ft_create_redirection(file, type);
	if (!redir)
		return;
	if (data->redirects == NULL)
		data->redirects = redir;
	else
	{
		tmp = data->redirects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}
*/
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
    }
}
/*
void	ft_sortredirect(t_data *data, int *i)
{
	t_token_list *toklist = data->toklist;
	//t_command *current = data->commands;

	if (ft_strcmp(toklist->tokens[*i], "<") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if there's a token after operator
			add_redirection(data, toklist->tokens[*i], 0); // 0 for input
	}
	else if (ft_strcmp(toklist->tokens[*i], ">") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if there's a token after operator
			add_redirection(data, toklist->tokens[*i], 1); // 1 for output
	}
	else if (ft_strcmp(toklist->tokens[*i], ">>") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if there's a token after operator
			add_redirection(data, toklist->tokens[*i], 2); // 2 for append
	}
	else if (ft_strcmp(toklist->tokens[*i], "<<") == 0)
	{
		if (++(*i) < toklist->token_count)	// check if there's a token after operator
			add_redirection(data, toklist->tokens[*i], 3); // 3 for here-doc
	}
}
*/

/*
// Function to handle Here-Doc redirection
void handle_here_doc(t_redirection *redir) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char *delimiter = redir->file; // Assuming the delimiter is stored in redir->file
    char buffer[1024];

    printf("Entering Here-Doc mode (type '%s' on a new line to terminate):\n", delimiter);
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break; // Exit loop on EOF
        }

        // Check if the input is the delimiter
        if (is_delimiter(buffer, delimiter)) {
            break;
        }

        // Write input to the pipe
        write(pipefd[1], buffer, strlen(buffer));
    }

    // Close the write end of the pipe to signal EOF to the reading process
    close(pipefd[1]);

    // Redirect standard input to the read end of the pipe
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
}
*/