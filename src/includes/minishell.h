#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# include "../../utils/libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_FD_REDIR_OUT,
	T_FD_REDIR_APPEND
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	int				index;
	char			**args;
	t_redir			*redirs;
	int				pipe_in;
	int				pipe_out;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_global
{
	t_env			*env;
	int				exit_status;
	int				signal_received;
}					t_global;

/* tokenizer */
t_token				*tokenize(char *input);
t_token				*new_token(char *value, t_token_type type);
t_token_type		get_operator_type(char *str, int i);
int					is_operator(char c);
void				add_token_back(t_token **head, t_token *new);
int					skip_spaces(char *input, int i);
int					handle_operator(char *input, int i, t_token **head);
int					handle_word(char *input, int i, t_token **head);
void				free_tokens(t_token *head);
char				*get_type_name(t_token_type type);
void				print_tokens(t_token *head);

/* parser */
t_cmd				*parse_token(t_token *tokens);
t_cmd				*create_cmd(void);
void				add_cmd_arg(t_cmd *cmd, char *value);
t_redir				*create_redir(int fd, char *file, t_token_type type);
void				redir_add_back(t_redir **head, t_redir *new);
void				redir_new(t_cmd *cmd, t_token_type type, char *op,
						char *value);
void				free_cmd(t_cmd *cmd);
int					is_redirection(t_token_type type);
t_token				*handle_redirection(t_cmd *cmd, t_token *current);
t_cmd				*handle_pipe(t_cmd *cmd);
int					handle_quotes(char *input, int i);

void				setup(const char *name);
void				init_shell(const char *name);

/* env_ops.c */
t_env				*env_find(t_env *env, char *key);
void				env_remove(t_global *global, char *key);
int					is_valid_identifier(char *s);

/* env_set.c */
void				env_update(t_env *node, char *value);
t_env				*env_new_node(char *key, char *value);
void				env_append(t_global *global, t_env *node);
t_env				*env_set(t_global *global, char *key, char *value);

/* env_utils.c */
int					env_list_len(t_env *env);
char				*env_join_kv(char *key, char *value);
char				**rebuild_env(t_env *env);
void				free_env_arr(char **env);
char				*find_path_env(t_env *env);

/* find_cmd.c */
char				*build_full_path(char *dir, char *cmd);
char				*find_command(char *cmd, t_env *env);

/* redir.c */
int					apply_redir_in(t_redir *redir);
int					apply_redir_out(t_redir *redir);
int					apply_redirs(t_cmd *cmd);

/* exec_cmd.c */
void				wire_pipes(int prev_fd, int *pipe_fd, int has_next);
void				print_cmd_not_found(char *name);
void				exec_child(t_cmd *cmd, int prev_fd, int *pipe_fd,
						t_global *global);

/* pipe_exe.c */
int					open_pipe(t_cmd *cmd, int *pipe_fd);
int					advance_pipe(int prev_fd, int *pipe_fd, t_cmd *cmd);
pid_t				fork_cmd(t_cmd *cmd, int prev_fd, int *pipe_fd,
						t_global *global);
void				wait_for_children(t_global *global);
void				pipe_exe(t_cmd *cmds, t_global *global);

/* builtin_dispatch.c */
int					is_builtin(char *name);
int					run_builtin(t_cmd *cmd, t_global *global);
int					run_builtin_with_redirs(t_cmd *cmd, t_global *global);
int					execute(t_cmd *cmds, t_global *global);

/* builtin_simple.c */
int					builtin_env(t_global *global);
int					builtin_pwd(void);
int					builtin_unset(t_cmd *cmd, t_global *global);

/* builtin_echo.c */
int					is_n_flag(char *arg);
int					echo_print(char **args, int start, int newline);
int					builtin_echo(t_cmd *cmd);

/* builtin_cd.c */
char				*cd_resolve_path(t_cmd *cmd, t_global *global);
void				cd_update_env(t_global *global, char *old_pwd);
int					builtin_cd(t_cmd *cmd, t_global *global);

/* builtin_export.c */
int					split_key_value(char *arg, char **key, char **value);
void				export_print_all(t_global *global);
int					export_one(char *arg, t_global *global);
int					builtin_export(t_cmd *cmd, t_global *global);

/* builtin_exit.c */
int					is_numeric(char *s);
int					builtin_exit(t_cmd *cmd, t_global *global);

void				free_array(char **dirs);
#endif