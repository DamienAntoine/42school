#include "../headers/minishell.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i])
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_next_line(int fd)
{
	int		i;
	int		bytesread;
	char	c;
	char	buf[BUFFER_SIZE + 1];

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((bytesread = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
		{
			buf[i++] = c;
			break ;
		}
		if (i >= BUFFER_SIZE - 1)
			break ;
		buf[i++] = c;
	}
	if (bytesread <= 0 && i == 0)
		return (NULL);
	buf[i] = '\0';
	return (ft_strdup(buf));
}//gnl is only here for testing (delete and use one from /includes/gnl later)




//lexer start
size_t ft_toklen(const char *str, const char *delim)
{
	size_t len = 0;
	int i;

	if (str == NULL || delim == NULL)
		return 0;
	while (str[len])
	{
		i = 0;
		while (delim[i])
		{
			if (str[len] == delim[i])
				return (len);
			i++;
		}
		len++;
	}
	return (len);
}

// strtok is like ft_split but it replaces delimiter characters with null characters,making every word of the string a token. It returns the next token everytime its called
char	*ft_strtok(char *str, const char *delimiter)
{
	static char *last; // keeps track of next token
	char	*start;
	char	*end;

	if (str == NULL)
		str = last;
	if (str == NULL || *str == '\0')
		return (NULL);
	start = str;
	end = start + ft_toklen(start, delimiter);
	if (*end != '\0')
	{
		*end = '\0';
		last = end + 1; // set the last pointer to the start of the next token
	}
	else
		last = NULL;
	return (start);
}

//lexer takes the whole command line and splits every word into a token to store them into token_list->tokens.
//example : ls -l = token 1 is "ls", token 2 is "-l"
char	**ft_tokenize(char *input)
{
	char	**args;
	int		i;
	char	*token;

	args = malloc(MAX_ARGS * sizeof(char *));
	i = 0;
	token = ft_strtok(input, " \t\n|<>");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = ft_strtok(NULL, " \t\n|<>");
	}
	args[i] = NULL;
	return (args);
}
//lexer end



//parser start

	//the parser takes the tokens from token_list struct and sorts them in corresponding variable of t_commands struct

//parser end



//sighandle start
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nMSL$> ", 8);
}
//sighandle end

t_data	*init_minishell(char **env)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->commands = malloc(sizeof(t_command));
	data->toklist = malloc(sizeof(t_token_list));
	data->env = malloc(sizeof(t_env));
	init_env(env, data->env);
	if (!data || !data->commands || !data->toklist)
		return (NULL);
	return (data);
}

#include <string.h>
int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_data			*data;

	if (argc > 1)
		exit(0);
	(void)argv;
	data = init_minishell(env);
	signal(SIGINT, handle_sigint); //handle ctrl+c
	while (1)
	{
		write(1, "MSL$> ", 6);
		input = get_next_line(STDIN_FILENO); // alias for '1' in unistd.h
		if (input == NULL) //ctrl + d
		{
			printf("Minishell Terminated (ctrl+d)\n");
			exit(0);
		}
		data->toklist->tokens = ft_tokenize(input); // splits inputs and stores tokens in the structure (lexer)

		if (synt_errors_check(data->toklist) == 0)    // checks tokens syntax and prints syntax errors
			data->commands = ft_sort_tokens(data->toklist, data->commands); // creates hierarchy and redirects them to corresponding functions (parser to executor)

        //start exec with checking commands and arguments
        
		//executor works with fork() and execve(), handles redirections (>, <, >>, <<) and pipes (|), and also handles error management(command not found, ...)
		//example of how lexer->parser->executor thing works: https://imgur.com/a/PTod73J

		free(input);
		free(data->toklist->tokens);
	}
	return (0);
}
