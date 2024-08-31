#ifndef MINISHELL_H
# define MINISHELL_H

#include "../includes/libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h> //for waitpid

# define BUFFER_SIZE 1024
# define MAX_ARGS 100

# define ERPIPE -101
# define ERCONS -102
# define ERREDIR -103
# define ERTOKEN -104
# define ERQUOTE -105
# define ERVARN -106

typedef struct s_data
{
	struct s_token_list		*toklist;
	struct s_command		*commands;
	struct s_redirection	*redirects;
	struct s_env			*env;
}	t_data;

typedef struct s_env
{
	char	*type;
	char	*value;
	struct s_env	*next;
}	t_env;

//maybe add a variable that counts the number of tokens in the input
//and somehow separate the command from the flags and store the flags in another variable
typedef struct s_command
{
	char					*cmds;				//command (ls, env, cd, ...)
	char					**args;				//arguments / flags (-l, "file.txt", ...)
	struct s_env			*env;	//!!!!!!!!!!ADDED
	struct s_redirection	*redirections;		//use this instead of the three variables above
	struct s_command		*next;				//pointer to next command if pipe (|)
}	t_command;

typedef struct s_redirection				//this struct is to be able to use multiple redirections in one command
{
	char					*file;			// file for redirection
	int						type;			// 0 for input ("<"), 1 for output (">"), 2 for append (">>"), 3 for ("<<")
	struct	s_redirection	*next;			// pointer to the next redirection
}	t_redirection;

typedef struct s_token_list
{
	char		**tokens;					//tokens created by the lexer
	int			token_count;
}	t_token_list;

//####  need to be sorted later  ########################

void	init_commands(t_data *data);
char	*trim_input(char *input);
void    ft_env(t_env *lst);


//######################### m_executor ##########################
//pipes.c
void	handle_pipe(t_data *data);

//executor.c
int	execute_command(t_data *data);
void	send_command(t_data *data);
//redirection.c
void	handle_redirection(t_data *data);



//#########################   builtins   ########################
void    ft_cd(t_command *current);
void    ft_echo(t_command *current);
void	ft_env(t_env *lst);
char	**env_list_to_array(t_env *env_list);
void	unset_env_var(t_env **env_list, char *name);
void	ft_pwd(t_env *cur_env);
void	print_export(t_env *env_list);
void    export_with_arg(t_env **env_list, char *name, char *value);
void	ft_exit(t_data *data, int status);
//void	exit();
//void	export();

//#########################   Utils   ########################
//utils_print.c
void printf_and_free(const char *message, void *ptr);
void perror_and_free(const char *message, void *ptr);

//utils_str.c
int is_delimiter(char c, const char *delimiter);
int		ft_isspace(int c);

//utils_error.c
void	error_msg(char *cmd, char *msg);



///////////////init.c//////////////
t_data	*init_minishell(char **env);
void    init_commands(t_data *data);




//includes/gnl.c
char *get_next_line(int fd);

//#########################   m_env   ########################



//init_env.c

char *find_env_value(t_env *env, const char *name);
void update_env_variable(t_env *env_list, char *name, char *value);
void init_env(char **env, t_env **cur_env);

//#########################   m_free   ########################
//free.c
void free_env_list(t_env *env);
void free_token_list(t_token_list *token_list);
void free_redirections(t_redirection *redirections);
void free_command(t_command *command);

//#########################   m_lexer   ########################
//synt_checks.c
int	synt_errors_check(t_token_list *toklist);
int consecutive_check(t_token_list *toklist, int i);
int	check_quotes(t_token_list *toklist);
int	is_valid_env_variable(const char *var);
int	ft_check_syntax(t_token_list *toklist);

//tokenize.c
char	**ft_tokenize(t_token_list *toklist, char *input);
char	*ft_strtok(char *str, const char *delimiter);
size_t ft_toklen(const char *str, const char *delim);

//#########################   m_parser   ########################
//create_redirects.c
void ft_add_redirection(t_command *current, char *file, int type);
t_redirection *ft_create_redirection(char *file, int type);

//sort_tokens.c
t_command	*ft_sort_tokens(t_token_list *toklist, t_command *table);
void	ft_sortloop(t_token_list *toklist, t_command *current, int i, int j);
t_command *ft_sortredirect(t_token_list *toklist, t_command *current, int *i);
t_command	*ft_sortpipes(t_command *current);

#endif
