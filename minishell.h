#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define PATH_MAX 4096

typedef enum s_enum
{
	t_string,
	t_rerror,
	t_outred,
	t_inred,
	t_append,
	t_heredoc,
	t_space,
	t_pipe,
}						t_toktype;

typedef enum s_enum2
{
	t_nquoted,
	t_dquoted,
	t_squoted,
}						t_strtype;

typedef struct s_tokens
{
	char				*content;
	t_toktype			type;
	t_strtype			s_type;
	int					expanded;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_files
{
	char				*name;
	char				*limiter;
	t_toktype			type;
	t_strtype			s_type;
	struct s_files		*next;
}						t_files;

typedef struct s_commands
{
	char				**options;
	t_files				*files;
	struct s_commands	*next;
}						t_commands;

typedef struct s_fds_controle
{
	int					read_from;
	int					write_on;
}						t_fds_controle;

typedef struct s_execute
{
	t_env				*env_list;
	int					status;
}						t_execute;

extern t_execute		*g_all_data;

//                                           MAIN

void					minishell(t_tokens **tokens, int x);

//                                          PARSING

int						check_syntax(char *str);
int						check_syntax2(t_tokens *tokens);
void					ft_tokeniser(char *str, t_tokens **tokens);
void					ft_handle_space(char *str, int *i, t_tokens **tokens);
void					get_env(char **env, t_env **our_env);
void					expand_env(t_tokens **tokens, t_env *env);
char					*get_the_value(char *token, int *i, t_env *env);
int						parsing(t_tokens **tokens, t_commands **commands,
							char *line, t_env *env);
char					**args_inserter(char **args, char *new_val,
							int is_unquoted);
void					generate_execution_input(t_tokens *tokens,
							t_commands **commands);
char					*ft_joiner(char *str, char c);
void					add_files(char *file_name, t_toktype type,
							t_strtype s_type, t_commands *currentNode);
void					concat_values(char **final_str, char *str);
void					ft_norm_help(char **value, char *token, int *i,
							t_env *env);
char					*ft_skip(char *token, int *i);

//                                         UTILS

t_tokens				*ft_lstlast(t_tokens *lst);
t_tokens				*ft_lstnew(char *content, t_toktype type,
							t_strtype s_type);
t_env					*ft_lstnew_env(char *key, char *value);
t_files					*ft_lstnew_files(char *name, char *limiter,
							t_toktype type, t_strtype s_type);
t_commands				*ft_lstnew_commands(void);
void					ft_lstadd_back(t_tokens **lst, t_tokens *new);
void					ft_lstadd_back_env(t_env **lst, t_env *new);
void					ft_lstadd_back_command(t_commands **lst,
							t_commands *new);
void					ft_lstadd_back_files(t_files **lst, t_files *new);
t_env					*ft_lstlast_env(t_env *lst);
t_commands				*ft_lstlast_command(t_commands *lst);
t_files					*ft_lstlast_file(t_files *lst);
void					ft_lstclear(t_tokens **lst);
void					ft_lstclear_env(t_env **env);
int						ft_lstsize_env(t_env *env);
t_env					*ft_copy_list(t_env *env);
char					*ft_itoa(int n);
long long				ft_atoi(const char *str);
void					handle_sig(int signal);
int						ft_strlen_double(char **tab);
int						ft_strlen(char *str);
char					**ft_split(char *str, char sep);
char					*ft_substr(char *s, int start, int len);
char					*ft_strdup(char *src);
char					*ft_strjoin(char *s1, char *s2);
int						ft_strcmp(const char *str1, const char *str2);
char					*ft_strchr(const char *str, int c);
int						ft_check_space(char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnstr(char *haystack, char *needle, size_t len);
char					*ft_strtrim(char *s1, char *set);
void					*ft_calloc(size_t nmemb, size_t size);
void					ft_bzero(void *s, size_t n);
// FREE
void					ft_free(char **str);
void					free_files(t_files *files);
void					free_commands(t_commands **commands);

// ft_dprintf

int						ft_dprintf(int fd, const char *format, ...);
int						ft_print_format(int fd, const char format, va_list ap);
int						ft_putaddr(int fd, size_t nbr);
int						ft_putchar(int fd, char c);
int						ft_puthex(int fd, unsigned int nbr, char format);
int						ft_putnbr_u(int fd, unsigned int n);
int						ft_putnbr(int fd, int n);
int						ft_putstr(int fd, char *str);
// BUILTINS UTILS

int						get_key_pos(char *key);
void					ft_unset_first(void);
void					ft_unset_mid(char *key);
void					ft_unset_last(void);
char					*ft_join_path(t_commands *commands, int size);
int						ft_check_slash(char *str);

// BUILTINS

void					ft_unset(t_commands *commands);
void					get_pwd(int fd);
void					ft_cd(t_commands *s_commands);
void					print_env(int fd);
void					ft_echo(t_commands *commands, int fd);

// EXPORT
void					ft_export(t_commands *command);
void					ft_swap_export(t_env *a, t_env *b);
void					ft_add_env_var(char *key, char *value);
void					ft_concat_var(char *key, char *value);
void					ft_add_key(char *key);
void					ft_add_key2(char *key);
t_env					*check_key(char *key);
char					*get_value(char *buffer, int i);
void					get_key(char *buffer);
void					ft_generate_key_value(char *buffer, int i, char *key);
void					process_export_vars(t_commands *command);
void					print_export(t_env *env);
char					*v_extract(char *buffer, char *num, char *sp_chars,
							int *i);
int						get_segments(char *key, int *start, int *end);
int						process_key_segment(char *key, int *start, int *end);
void					ft_sort_env(t_env *env);

// EXIT
void					ft_exit(t_commands *commands);

// EXECUTION

void					ft_execute(t_commands **commands);
void					ft_handel_herdoc(t_commands *commands);
char					**ft_convert_env(t_env *env_list);
char					*ft_check_path(t_commands *commands, char *cmd,
							char **env);
int						is_executable(const char *path);
char					*ft_check_cmd_helper(t_commands *commands, char *cmd,
							char **env);
int						ft_cmd_size(t_commands *commands);
void					ft_serve_builtin(t_commands *commands, int fd);
void					ft_proc_help(t_commands *commands, int *pids,
							char **env, t_fds_controle *fds);
void					ft_one_cmd(t_commands *commands, int *pids, char **env);
// you need to add this the part of the parssing
char					*ft_expand(char *token, t_env *env);
void					ft_help_exp(t_tokens *tmp, t_tokens *old_prev,
							t_env *env);
void					ft_help_exp_2(t_tokens **tmp, t_tokens **old_prev);
void					ft_wait_proc(int *pids, int size);

int						ft_check_builtin(char *cmd);
// multi commands
void					ft_fcmd_dup(int *pipe_fd, t_fds_controle *fds);
void					ft_mcmd_dup(int *pipe_fd, t_fds_controle *fds);
void					ft_lcmd_dup(int *pipe_fd, t_fds_controle *fds);
void					ft_first_cmd(t_commands *tmp, t_commands *commands,
							int *pipe_fd, char **env);
void					ft_mid_cmd(t_commands *tmp, t_commands *commands,
							int *pipe_fd, char **env);
void					ft_last_cmd(t_commands *tmp, t_commands *commands,
							int *pipe_fd, char **env);

// exec utils
int						ft_cmd_size(t_commands *commands);
t_fds_controle			*ft_handel_fds(t_files *files);
int						ft_check_builtin(char *cmd);
void					ft_chnage_name(t_files **files, int i);

// wild card
void					ft_check_wildcard(t_tokens **tokens);
void					ft_replace_files(t_tokens **tokens, char *file_name,
							int flag);
int						ft_check_help(int i, char *tmp_file, char **cards,
							char *word);
int						ft_check_name(char *file, char *word);
void					ft_dir_by_dir(t_tokens **token, char *word);
void					ft_take_dir(t_tokens **token);
void					ft_free_all(t_commands *commands, char **env);
void					ft_start_proc_help(int *pids);
int						ft_pipe_fork(int *pipe_fd);

#endif