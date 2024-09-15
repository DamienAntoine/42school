#include "../../headers/minishell.h"

void ft_grep(t_data *data)
{
    char buffer[BUFFER_SIZE];
    int file;
    ssize_t bytes_read;
    char *match;
    char *line;
    int i = 1; // Start from the second argument (file names)
    char *pattern = data->commands->args[0]; // Pattern is stored in args[0]

    if (pattern == NULL)
    {
        ft_putstr_fd("Usage: grep [PATTERN] [FILE...]\n", STDERR_FILENO);
        return;
    }

    // Loop through each file argument and search for the pattern
    while (data->commands->args[i])
    {
        file = open(data->commands->args[i], O_RDONLY);
        if (file == -1)
        {
            perror("grep");
            i++;
            continue;
        }

        // Read the file in chunks
        while ((bytes_read = read(file, buffer, BUFFER_SIZE - 1)) > 0)
        {
            buffer[bytes_read] = '\0'; // Null-terminate the buffer

            // Use ft_strtok to split the buffer into lines
            line = ft_strtok(buffer, "\n");
            while (line != NULL)
            {
                // Check if the pattern exists in the line
                match = ft_strstr(line, pattern);
                if (match != NULL)
                {
                    ft_putstr_fd(line, STDOUT_FILENO);
                    ft_putchar_fd('\n', STDOUT_FILENO); // Print a newline after the matching line
                }
                line = ft_strtok(NULL, "\n");
            }
        }

        close(file);
        i++;
    }
}
/*
void ft_grep(t_data *data)
{
    char buffer[BUFFER_SIZE];
    int file;
    ssize_t bytes_read;
    char *match;
    int i = 1; 
    char *pattern = data->commands->args[0]; // Pattern is stored in args[0]

    if (pattern == NULL)
    {
        ft_putstr_fd("Usage: grep [PATTERN] [FILE...]\n", STDERR_FILENO);
        return;
    }

    printf("Pattern: %s\n", pattern); //debug

    // Loop through each file argument and search for the pattern
    while (data->commands->args[i])
    {
        printf("Opening file: %s\n", data->commands->args[i]);
        file = open(data->commands->args[i], O_RDONLY);
        if (file == -1)
        {
            perror("grep");
            i++;
            continue;
        }

        // Read from the file and search for the pattern
        while ((bytes_read = read(file, buffer, BUFFER_SIZE -1 )) > 0)
        {
            buffer[bytes_read] = '\0'; // Null-terminate the buffer
            match = strstr(buffer, pattern); // Search for the pattern
            if (match != NULL)
            {
                ft_putstr_fd(buffer, STDOUT_FILENO); // Output the line if the pattern is found
            }
        }
        if (bytes_read == -1)
            perror("read");

        close(file);
        i++;
    }
}
*/



void ft_cat(t_data *data)
{
    int fd;
    char buffer[1024];  // Buffer to read file contents
    ssize_t bytes_read;
    int i = 0;  // Start from the first argument (file names)

    if (data->commands->args[0] == NULL)
    {
        ft_putstr_fd("cat: missing file operand\n", STDERR_FILENO);
        return;
    }

    // Loop through each file argument and print its content
    while (data->commands->args[i])
    {
        fd = open(data->commands->args[i], O_RDONLY);  // Open file in read-only mode
        if (fd == -1)
        {
            perror("cat");
            i++;
            continue;
        }

        // Read the file content in chunks and print it to the output
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
        {
            if (write(STDOUT_FILENO, buffer, bytes_read) == -1)  // Check if write fails
            {
                perror("write");
                close(fd);
                return;
            }
        }

        if (bytes_read == -1)
        {
            perror("read");
        }

        close(fd);  // Close the file descriptor after reading the file
        i++;
    }
}
