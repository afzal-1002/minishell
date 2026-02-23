/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:42 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/23 14:32:09 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "../../utils/libft/libft.h"
# include <fcntl.h>
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
void				add_arg(t_cmd *cmd, char *value);

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

#endif
