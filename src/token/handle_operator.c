#include "../../includes/minishell.h"

int	handle_operator(char *input, int i, t_token **head)
{
	t_token_type	type;
	t_token			*new;
	char			*value;
	int				len;

	type = get_operator_type(input, i);

	if (type == T_HEREDOC || type == T_REDIR_APPEND)
		len = 2;
	else
		len = 1;

	value = ft_substr(input, i, len);
	new = new_token(value, type);
	add_token_back(head, new);

	return (i + len);
}
