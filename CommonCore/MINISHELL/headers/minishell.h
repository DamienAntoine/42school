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
#include <sys/wait.h> //for waitpid, WIFEXITED, WEXITSTATUS
#include <termios.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>


# define BUFFER_SIZE 1024
# define MAX_ARGS 100

# define ERPIPE -101
# define ERCONS -102
# define ERREDIR -103
# define ERTOKEN -104
# define ERQUOTE -105
# define ERVARN -106

typedef struct s_state
{
	int	last_exit_status;
}	t_state;

typedef struct s_data
{
	struct s_token_list		*toklist;
	struct s_command		*commands;
	struct s_redirection	*redirects;
	struct s_env			*env;
	t_state			state;   //added for echo
}	t_data;

typedef struct s_env
{
	char	*type;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct s_command
{
	char					*cmds;				//command (ls, env, cd, ...)
	char					**args;				//arguments / flags (-l, "file.txt", ...)
	struct s_command		*next;				//pointer to next command if pipe (|)
}	t_command;

typedef struct s_redirection					//this struct is to be able to use multiple redirections in one command
{
	char					*file;				// file for redirection
	int						type;				// 0 for input ("<"), 1 for output (">"), 2 for append (">>"), 3 for ("<<")
	struct	s_redirection	*next;				// pointer to the next redirection
}	t_redirection;

typedef struct s_token_list
{
	char		**tokens;
	int			token_count;
}	t_token_list;

//####  need to be sorted later  ########################

void print_env_variable(const char *arg, t_data *data);
char *remove_balanced_quotes(const char *input);
int		are_quotes_balanced(const char *input);
void	printcommands(t_data *data);
void	init_commands(t_data *data);
char	*trim_input(char *input);
void    ft_env(t_env *lst);
char	*get_current_directory(void);
void	free_minishell(t_data *data);
void	free_split(char **split);
int		is_builtin(char *cmd);
void	execute_builtin(t_command *cmdtable, t_data *data);
char	*get_command_path(const char *cmd);
char *get_full_input(void);
void add_redirection(t_data *data, char *file, int type);
void setup_redirection(t_redirection *redir);
int handle_here_doc(t_redirection *redir);
char	*ft_strstr(const char *haystack, const char *needle);
void ft_cat(t_data *data);
void ft_grep(t_data *data);
void ignore_sigquit();
void setup_terminal();
void	handle_sigint(int sig);
//void update_exit_status(t_data *data, long long status);
void set_exit_status(long status, t_data *data);




//######################### m_executor ##########################
//pipes.c
void	handle_pipe(t_data *data, int num_commands);

//executor.c
int		execute_command(t_data *data);
void	send_command(t_data *data);
//redirection.c
int	open_redirection(t_redirection *redir);



//#########################   builtins   ########################
void    ft_cd(t_data *cur);
void    ft_echo(t_data *data);
void	ft_env(t_env *lst);
char	**env_list_to_array(t_env *env_list);
void    handle_unset(t_env **lst, char **args);

void	ft_pwd(t_env *cur_env);
void	print_export(t_env *env_list, t_data *data);
//void    handle_export(t_env **lst, char **args, t_state *state);
void	handle_export(t_data *data);

void	ft_exit(t_data *data);
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
void update_or_add_env_variable(t_env **env_list, const char *name, const char *value);
void init_env(char **env, t_env **cur_env);

//#########################   m_free   ########################
//free.c
void free_env_list(t_env *env);
void free_token_list(t_token_list *token_list);
void free_redirections(t_redirection *redirections);
void free_command(t_command *command);

//#########################   m_lexer   ########################
//synt_checks.c
int	has_synt_errors(t_token_list *toklist);
int is_consecutive(t_token_list *toklist, int i);
int	has_quotes(t_token_list *toklist);
int	is_valid_env_variable(const char *var);
int	ft_check_syntax(t_token_list *toklist);

//tokenize.c
char	**ft_tokenize(t_token_list *toklist, char *input);
char	*ft_strtok(char *str, const char *delimiter);
size_t ft_toklen(const char *str, const char *delim);

//#########################   m_parser   ########################
//create_redirects.c
//void ft_add_redirection(t_data *data, char *file, int type);
t_redirection *ft_create_redirection(char *file, int type);

//sort_tokens.c
void	ft_sort_tokens(t_data *data);
void	ft_sortloop(t_data *data, int i, int j);
void	ft_sortredirect(t_data *data, int *i);
//void	ft_sortpipes(t_data *data);
void	ft_sortpipes(t_command *commands);


//t_command	*ft_sort_tokens(t_token_list *toklist, t_command *table);
//void	ft_sortloop(t_token_list *toklist, t_command *current, int i, int j);
//t_command *ft_sortredirect(t_token_list *toklist, t_command *current, int *i);
//t_command	*ft_sortpipes(t_command *current);

#endif
