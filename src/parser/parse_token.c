#include "../../includes/minishell.h"

t_cmd	*parse_token(t_token *tokens)
{
	t_token	*current;
	t_cmd	*cmd;
	t_cmd	*head;

	head = create_cmd();
	if (!head)
		return (NULL);
	cmd = head;
	current = tokens;
	while (current)
	{
		if (current->type == T_WORD)
		{
			add_arg(cmd, current->value);
		}
		else if (current->type == T_REDIR_OUT || current->type == T_REDIR_IN)
		{
			// if (current->next && current->next->type == T_WORD)
			// {
			// 	add_redir(&cmd, current->type, current->next->value);
			// 	current = current->next;
			// }
		}
		else if (current->type == T_PIPE)
		{
			cmd->next = create_cmd();
			cmd = cmd->next;
		}
		current = current->next;
	}
	return (head);
}
