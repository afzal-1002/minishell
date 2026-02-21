#include "../../includes/minishell.h"


t_token_type get_operator_type(char *str, int i)
{
	if (str[i] == '|' )
		return (T_PIPE);
	if (str[i] == '<' && str[i + 1] == '<')
		return (T_HEREDOC);
	if (str[i] == '<')
		return (T_REDIR_IN);
	if (str[i] == '>' && str[i + 1] == '>')
		return (T_REDIR_APPEND);
	if (str[i] == '>')
		return (T_REDIR_OUT);
	return (T_WORD);
}
