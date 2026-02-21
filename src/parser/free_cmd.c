#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*redir;
	t_redir	*tmp;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	redir = cmd->redirs;
	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
	free(cmd);
}
