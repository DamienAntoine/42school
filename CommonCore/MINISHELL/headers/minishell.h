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
#include <sys/stat.h>


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

typedef struct s_history
{
    char *command;
    struct s_history *prev;
    struct s_history *next;
} t_history;

typedef struct s_data
{
	struct s_token_list		*toklist;
	struct s_command		*commands;
	struct s_env			*env;
	t_state					state;
	int						error_occurred;
	t_history				*history;
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
	struct s_redirection	*redirects;
	struct s_command		*next;				//pointer to next command if pipe (|)
}	t_command;

typedef struct s_redirection					//this struct is to be able to use multiple redirections in one command
{
	char					*file;				// file for redirection
	int						type;				// 0 for input ("<"), 1 for output (">"), 2 for append (">>"), 3 for ("<<")
	int						error_flag;
	struct	s_redirection	*next;				// pointer to the next redirection
}	t_redirection;

typedef struct s_token_list
{
	char		**tokens;
	int			token_count;
}	t_token_list;


//####  need to be sorted later  ########################

void free_new_node(t_env *new_node);
t_env *create_new_node(const char *env_entry);
void add_node_to_list(t_env **cur_env, t_env *new_node);
void	print_escape(char *arg);
int	is_in_single_quote(const char *arg, int position);
void	ft_strlcat_char(char *dst, char c, size_t dstsize);
char	*ft_strcat(char *dest, const char *src);
void	handle_flags(t_data *data, int *i, int *n_flag);
char	*get_current_directory(void);
int	handle_home_directory(t_data *cur, char **target_dir, char *oldpwd);
int	handle_oldpwd(t_data *cur, char **target_dir, char *oldpwd);
int	handle_env_variable(t_data *cur, char **target_dir, char *oldpwd);
int	validate_arguments(t_data *cur, char *oldpwd);
void	export_with_arg(t_env **env_list, char *arg, t_data *data);
int	create_new_var(t_env **current, char *name, char *new_value);
void	update_existing_var(t_env *current, char *new_value, t_data *data);
t_env	*clone_node(t_env *node);
void	sorted_insert(t_env **sorted_list, t_env *new_node);
t_data  *init_toklist(t_data *data);
t_data    *malloc_commands(t_data *data);
t_history *add_command_to_history(t_history **history, const char *command);
char	*process_env_token(const char *str, t_data *data);
void	ft_strlcat_char(char *dst, char c, size_t dstsize);
char	*expand_variable(const char *var_name, t_data *data);
size_t	estimate_buffer_size(const char *str, t_data *data);
void print_env_variable(const char *arg, t_data *data);
char *remove_balanced_quotes(const char *input);
int		are_quotes_balanced(const char *input);
void	printcommands(t_data *data);
void	init_commands(t_data *data);
char	*trim_input(char *input);
char	*get_current_directory(void);
void	free_minishell(t_data *data);
void	free_split(char **split);
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmdtable, t_data *data);
char	*get_command_path(const char *cmd);
char *get_full_input(void);
void add_redirection(t_command *current_command, char *file, int type);
int setup_redirection(t_redirection *redir);
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
int handle_pipes(t_data *data, t_command *cmdtable, int num_commands);

//executor.c
int		execute_command(t_data *data);
int		send_command(t_data *data);
//redirection.c
int	open_redirection(t_redirection *redir);



//#########################   builtins   ########################
int    ft_cd(t_data *cur);
int    ft_echo(t_data *data);
int	ft_env(t_env *lst);
char	**env_list_to_array(t_env *env_list);
int    handle_unset(t_env **lst, char **args);

int	ft_pwd(t_env *cur_env);
void	print_export(t_env *env_list, t_data *data);
//void    handle_export(t_env **lst, char **args, t_state *state);
int	handle_export(t_data *data);

int	ft_exit(t_data *data);
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
void	up_env(t_env **env_list, const char *name, const char *value);
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
char	**ft_tokenize(t_data *data, char *input);
char	*ft_strtok(char *str, const char *delimiter);
size_t ft_toklen(const char *str, const char *delim);

//#########################   m_parser   ########################
//create_redirects.c
//void ft_add_redirection(t_data *data, char *file, int type);
t_redirection *ft_create_redirection(char *file, int type);

//sort_tokens.c
void	ft_sort_tokens(t_data *data);
void	ft_sortloop(t_data *data, int i, int j);
void ft_sortredirect(t_data *data, t_command *current_command, int *i);
//void	ft_sortpipes(t_data *data);
void	ft_sortpipes(t_command *commands);


//t_command	*ft_sort_tokens(t_token_list *toklist, t_command *table);
//void	ft_sortloop(t_token_list *toklist, t_command *current, int i, int j);
//t_command *ft_sortredirect(t_token_list *toklist, t_command *current, int *i);
//t_command	*ft_sortpipes(t_command *current);

#endif
