#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

# define BUFFER_SIZE 1024
# define MAX_ARGS 100


//maybe add a variable that counts the number of tokens in the input
//and somehow separate the command from the flags and store the flags in another variable
typedef struct s_command
{
	char				*cmds;				//command (ls, env, cd, ...)
	char				**args;				//arguments / flags (-l, "file.txt", ...)
	t_redirection		*redirections;		//use this instead of the three variables above
	struct s_command	*next;				//pointer to next command if pipe (|)
}	t_command;

typedef struct s_redirection				//this struct is to be able to use multiple redirections in one command
{
	char					*file;			// file for redirection
	int						type;			// 0 for input ("<"), 1 for output (">"), 2 for append (">>")
	struct	s_redirection	*next;			// pointer to the next redirection
} t_redirection;

typedef struct s_token_list
{
	char		**tokens;					//tokens created by the lexer
	int			token_count;
}	t_token_list;

#endif
