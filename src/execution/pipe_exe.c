#include "../includes/minishell.h"

int	open_pipe(t_cmd *cmd, int *pipe_fd)
{
	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
	return (0);
}

int	advance_pipe(int prev_fd, int *pipe_fd, t_cmd *cmd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

pid_t	fork_cmd(t_cmd *cmd, int prev_fd, int *pipe_fd, t_global *global)
{
	pid_t	pid;

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

void	wait_all(t_global *global)
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

void	pipe_exe(t_cmd *cmds, t_global *global)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		prev_fd;

	current = cmds;
	prev_fd = -1;
	while (current)
	{
		if (open_pipe(current, pipe_fd) == -1)
		{
			global->exit_status = 1;
			return ;
		}
		if (fork_cmd(current, prev_fd, pipe_fd, global) == -1)
		{
			global->exit_status = 1;
			return ;
		}
		prev_fd = advance_pipe(prev_fd, pipe_fd, current);
		current = current->next;
	}
	wait_all(global);
}
