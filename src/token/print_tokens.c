#include "../../includes/minishell.h"

void	print_tokens(t_token *head)
{
	while (head)
	{
		printf("Value: %-10s | Type: %s\n", head->value,
			get_type_name(head->type));
		head = head->next;
	}
}
