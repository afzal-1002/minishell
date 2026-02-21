#include "../../includes/minishell.h"

t_token	*tokenize(char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			i = handle_operator(input, i, &head);
		else
			i = handle_word(input, i, &head);
	}
	return (head);
}
