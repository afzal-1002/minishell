/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:50:51 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 09:50:52 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	wait_for_children(global);
}
