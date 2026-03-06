#include "../includes/minishell.h"

void	wait_for_children(t_global *global)
{
	int	status;
	int	last;

	last = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last = 128 + WTERMSIG(status);
	}
	global->exit_status = last;
}
