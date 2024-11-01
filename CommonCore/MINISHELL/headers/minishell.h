#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

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
	int						last_exit_status;
}							t_state;

typedef struct s_history
{
	char					*command;
	struct s_history		*prev;
	struct s_history		*next;
}							t_history;

typedef struct s_data
{
	struct s_token_list		*toklist;
	struct s_command		*commands;
	struct s_env			*env;
	t_state					state;
	int						error_occurred;
	t_history				*history;
}							t_data;

typedef struct s_env
{
	char					*type;
	char					*value;
	struct s_env			*next;
	int						in_single_quotes;
	int						in_double_quotes;
	char					*result;
	size_t					buffer_size;
}							t_env;

typedef struct s_command
{
	char					*cmds;
	char					**args;
	struct s_redirection	*redirects;
	struct s_command		*next;
}							t_command;

typedef struct s_redirection
{
	char					*file;
	int						type;
	int						error_flag;
	int						heredoc_fd;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_token_list
{
	char					**tokens;
	int						token_count;
}							t_token_list;

typedef struct s_quote_state
{
	int						in_single_quotes;
	int						in_double_quotes;
}							t_quote_state;

//####  need to be sorted later  ########################
char						*initialize_str(char *str, const char *delimiter,
								char **last);
char						*check_special_characters(char *str, char *start,
								char **last);
void						toggle_quotes(char c, int *in_single_quotes,
								int *in_double_quotes);
char						*initialize_tokenizer(char *str,
								const char *delimiter, char **last);

char						*process_token_character(char *str, char *start,
								const char *delimiter, char **last);
void						close_all_pipes(int *pipes);
int							quotes_check(const char *input);
void						process_quotes(const char *str, int *i,
								t_data *data);
char						*handle_quotes(const char *str, t_data *data);
int							is_in_quotes(const char *arg, int position);

char						*expand_variable(const char *var_name,
								t_data *data);
size_t						estimate_buffer_size(const char *str, t_data *data);
void						handle_single_quotes(const char *str, int *i,
								t_data *data);
void						handle_double_quotes(const char *str, int *i,
								t_data *data);
void						handle_unprocessed_string(const char *str, int *i,
								int *start, t_data *data);

int							handle_null_data(t_data *data);
int							handle_null_data(t_data *data);
int							handle_builtin_command(t_data *data,
								int *exit_code);
int							prepare_command(t_data *data, char ***envp,
								char ***full_args);
int							handle_builtin_cmd(t_data *data, char **envp,
								char **full_args);

int							handle_is_directory(t_data *data, char *exec_target,
								struct stat path_stat);
int							handle_permission_denied(t_data *data,
								char *exec_target);
int							handle_exec_permission(t_data *data,
								char *exec_target, struct stat path_stat);
int							handle_exec_error_if_part(t_data *data,
								char *exec_target, struct stat path_stat);
int							handle_exec_error_else_part(t_data *data,
								char *exec_target);
int							execute_child_process(t_command *cmdtable,
								char **full_args, char **envp, t_data *data);
int							execute_external_command(t_command *cmdtable,
								char **full_args, char **envp, t_data *data);
int							handle_parent_process(pid_t pid);
int							handle_exec_error(t_data *data, char *exec_target);
int							check_redirection_before_fork(t_data *data);
int							execute_builtin(t_command *cmdtable, t_data *data);
int							handle_exec_error(t_data *data, char *exec_target);
char						**prepare_full_args(t_command *cmdtable,
								int *arg_count);
int							execute_builtin_command(t_command *cmdtable,
								t_data *data);
int							open_redirection(t_redirection *redir);
int							handle_input_redirection(t_redirection *redir);
int							handle_output_redirection(t_redirection *redir);
int							setup_redirection(t_redirection *redir);
int							process_heredoc_lines(const char *delimiter,
								int write_fd);
int							handle_here_doc(t_redirection *redir);
int							output_redirection_exists(t_redirection *redirects);
void						close_pipes(int pipes[], int num_commands);
int							create_pipes(int pipes[], int num_commands);
int							wait_for_children(t_data *data, pid_t *child_pids,
								int num_commands);
int							ft_cmdsize(t_command *lst);
void						free_new_node(t_env *new_node);
t_env						*create_new_node(const char *env_entry);
void						add_node_to_list(t_env **cur_env, t_env *new_node);
void						print_escape(char *arg);
int							is_in_single_quote(const char *arg, int position);
void						ft_strlcat_char(char *dst, char c, size_t dstsize);
char						*ft_strcat(char *dest, const char *src);
void						handle_flags(t_data *data, int *i, int *n_flag);
char						*get_current_directory(void);
int							handle_home_directory(t_data *cur,
								char **target_dir, char *oldpwd);
int							handle_oldpwd(t_data *cur, char **target_dir,
								char *oldpwd);
int							handle_env_variable(t_data *cur, char **target_dir,
								char *oldpwd);
int							validate_arguments(t_data *cur, char *oldpwd);
void						export_with_arg(t_env **env_list, char *arg,
								t_data *data);
int							create_new_var(t_env **current, char *name,
								char *new_value);
void						update_existing_var(t_env *current, char *new_value,
								t_data *data);
t_env						*clone_node(t_env *node);
void						sorted_insert(t_env **sorted_list, t_env *new_node);
t_data						*init_toklist(t_data *data);
t_data						*malloc_commands(t_data *data);
t_history					*add_command_to_history(t_history **history,
								const char *command);
char						*process_env_token(const char *str, t_data *data);
void						ft_strlcat_char(char *dst, char c, size_t dstsize);
char						*expand_variable(const char *var_name,
								t_data *data);
size_t						estimate_buffer_size(const char *str, t_data *data);
void						print_env_variable(const char *arg, t_data *data);
char						*remove_balanced_quotes(const char *input);
int							are_quotes_balanced(const char *input);
void						printcommands(t_data *data);
void						init_commands(t_data *data);
char						*trim_input(char *input);
char						*get_current_directory(void);
void						free_minishell(t_data *data);
void						free_split(char **split);
int							is_builtin(char *cmd);
int							execute_builtin(t_command *cmdtable, t_data *data);
char						*get_command_path(t_data *data, const char *cmd);
char						*get_full_input(void);
void						add_redirection(t_command *current_command,
								char *file, int type);
int							handle_here_doc(t_redirection *redir);
char						*ft_strstr(const char *haystack,
								const char *needle);
void						ft_cat(t_data *data);
void						ft_grep(t_data *data);
void						ignore_sigquit(void);
void						setup_terminal(void);
void						handle_sigint(int sig);
void						set_exit_status(long status, t_data *data);

//######################### m_executor ##########################
// pipes.c
int							handle_pipes(t_data *data, t_command *cmdtable,
								int num_commands);

// executor.c
int							execute_command(t_data *data);
int							send_command(t_data *data);
// redirection.c
int							open_redirection(t_redirection *redir);

//#########################   builtins   ########################
int							ft_cd(t_data *cur);
int							ft_echo(t_data *data);
int							ft_env(t_env *lst);
char						**env_list_to_array(t_env *env_list);
int							handle_unset(t_env **lst, char **args);

int							ft_pwd(t_env *cur_env);
void						print_export(t_env *env_list, t_data *data);
int							handle_export(t_data *data);

int							ft_exit(t_data *data);

//#########################   Utils   ########################
// utils_print.c
void						printf_and_free(const char *message, void *ptr);
void						perror_and_free(const char *message, void *ptr);

// utils_str.c
int							is_delimiter(char c, const char *delimiter);
int							ft_isspace(int c);

// utils_error.c
void						error_msg(char *cmd, char *msg);

///////////////init.c//////////////
t_data						*init_minishell(char **env);
void						init_commands(t_data *data);

// includes/gnl.c
char						*get_next_line(int fd);

//#########################   m_env   ########################

// init_env.c

char						*find_env_value(t_env *env, const char *name);
void						up_env(t_env **env_list, const char *name,
								const char *value);
void						init_env(char **env, t_env **cur_env);

//#########################   m_free   ########################
// free.c
void						free_env_list(t_env *env);
void						free_token_list(t_token_list *token_list);
void						free_redirections(t_redirection *redirections);
void						free_command(t_command *command);

//#########################   m_lexer   ########################
// synt_checks.c
int							has_synt_errors(t_token_list *toklist);
int							is_consecutive(t_token_list *toklist, int i);
int							has_quotes(t_token_list *toklist);
int							is_valid_env_variable(const char *var);
int							ft_check_syntax(t_token_list *toklist);

// tokenize.c
char						**ft_tokenize(t_data *data, char *input);
char						*ft_strtok(char *str, const char *delimiter);
size_t						ft_toklen(const char *str, const char *delim);

//#########################   m_parser   ########################
// create_redirects.c
t_redirection				*ft_create_redirection(char *file, int type);

// sort_tokens.c
int							ft_sort_tokens(t_data *data);
int							ft_sortloop(t_data *data, int i, int j);
int							ft_sortredirect(t_data *data,
								t_command *current_command, int *i);
void						ft_sortpipes(t_command *commands);

#endif
