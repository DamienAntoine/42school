#ifndef MINISHELL_H
# define MINISHELL_H

#include "../includes/libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>	//sam: added for error msg for b_cd.c

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
	int						type;			// 0 for input ("<"), 1 for output (">"), 2 for append (">>")
	struct	s_redirection	*next;			// pointer to the next redirection
}	t_redirection;

typedef struct s_token_list
{
	char		**tokens;					//tokens created by the lexer
	int			token_count;
}	t_token_list;


t_data	*init_minishell(char **env);
void	init_commands(t_data *data);
char	*trim_input(char *input);
///////////////////////////builtins///////////////////////////////////////////
void    cd(t_command *current);
void    echo(t_command *current);
void	env(t_env *lst);
void	ft_pwd(t_env *cur_env);
//void	exit();
//void	export();
//void	pwd();
//void	unset();
//utils.c
int is_delimiter(char c, const char *delimiter);
int		ft_isspace(int c);
///////////////init//////////////
void    init_commands(t_data *data);



void printf_and_free(const char *message, void *ptr);
void perror_and_free(const char *message, void *ptr);
char *get_next_line(int fd);

///////////////////////////m_env//////////////////////////////////////////////
//env_value.c
void update_env_value(t_env **env, const char *name, const char *new_value);
char *find_env_value(t_env *env, const char *name);

//init_env.c
void unset_env_variable(t_env **env_list, char *name);
void update_env_variable(t_env *env_list, char *name, char *value);
void init_env(char **env, t_env **cur_env);

///////////////////////////m_free////////////////////////////////////////////
//free.c
void free_env_list(t_env *env);
void free_token_list(t_token_list *token_list);
void free_redirections(t_redirection *redirections);
void free_command(t_command *command);

///////////////////////////m_lexer///////////////////////////////////////////
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

///////////////////////////m_parser//////////////////////////////////////////
//create_redirects.c
void ft_add_redirection(t_command *current, char *file, int type);
t_redirection *ft_create_redirection(char *file, int type);

//sort_tokens.c
t_command	*ft_sort_tokens(t_token_list *toklist, t_command *table);
void	ft_sortloop(t_token_list *toklist, t_command *current, int i, int j);
t_command *ft_sortredirect(t_token_list *toklist, t_command *current, int *i);
t_command	*ft_sortpipes(t_command *current);

#endif
