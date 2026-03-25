/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:50:51 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:18:49 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_fork_error(pid_t pid, t_global *global)
{
	if (pid == -1)
	{
		global->exit_status = 1;
		g_signal_state = 0;
		return (1);
	}
	return (0);
}

void	pipe_exe(t_cmd *cmds, t_global *global)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	current = cmds;
	prev_fd = -1;
	g_signal_state = 1;
	while (current)
	{
		if (open_pipe(current, pipe_fd) == -1)
		{
			global->exit_status = 1;
			return ;
		}
		pid = fork_cmd(current, prev_fd, pipe_fd, global);
		if (handle_fork_error(pid, global))
			return ;
		(void)pid;
		prev_fd = advance_pipe(prev_fd, pipe_fd, current);
		current = current->next;
	}
	wait_for_children(global);
	g_signal_state = 0;
}
