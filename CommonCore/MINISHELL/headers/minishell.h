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
	char		*cmds;				//command (ls, env, cd, ...)
	char		**args;				//arguments / flags (-l, "file.txt", ...)
	char		*input_redirect;	//'<'
	char		*output_redirect;	//'>'
	int			append;				//flag for '>>'
	struct s_command	*next;				//pointer to next command if pipe (|)
}	t_command;

typedef struct s_token_list
{
	char		**tokens;			//tokens created by the lexer
	int			token_count;
}	t_token_list;

#endif
