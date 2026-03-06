#include "../includes/minishell.h"

pid_t	fork_cmd(t_cmd *cmd, int prev_fd, int *pipe_fd, t_global *global)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_child(cmd, prev_fd, pipe_fd, global);
	return (pid);
}