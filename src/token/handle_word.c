#include "../../includes/minishell.h"

int	handle_word(char *input, int i, t_token **head)
{
	int		start;
	char	*value;
	t_token	*new;

	start = i;
	while (input[i] && input[i] != ' ' && !is_operator(input[i]))
		i++;

	value = ft_substr(input, start, i - start);
	new = new_token(value, T_WORD);
	add_token_back(head, new);

	return (i);
}
