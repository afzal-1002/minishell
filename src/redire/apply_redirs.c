#include "../includes/minishell.h"

int	apply_redirs(t_cmd *cmd)
{
	int		status;
	t_redir	*cur;

	cur = cmd->redirs;
	while (cur)
	{
		status = 0;
		if (cur->type == T_REDIR_IN || cur->type == T_HEREDOC)
			status = apply_redir_in(cur);
		else if (cur->type == T_REDIR_OUT || cur->type == T_REDIR_APPEND
			|| cur->type == T_FD_REDIR_OUT || cur->type == T_FD_REDIR_APPEND)
			status = apply_redir_out(cur);
		if (status == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
