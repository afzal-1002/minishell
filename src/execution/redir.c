#include "../includes/minishell.h"

int	apply_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redir_out(t_redir *redir)
{
	int	fd;
	int	flags;

	if (redir->type == T_REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(redir->file, flags, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirs(t_cmd *cmd)
{
	t_redir	*r;
	int		ret;

	r = cmd->redirs;
	ret = 0;
	while (r && ret == 0)
	{
		if (r->type == T_REDIR_IN)
			ret = apply_redir_in(r);
		else if (r->type == T_REDIR_OUT || r->type == T_REDIR_APPEND)
			ret = apply_redir_out(r);
		r = r->next;
	}
	return (ret);
}
