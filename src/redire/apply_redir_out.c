#include "../includes/minishell.h"

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
	if (dup2(fd, redir->fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
