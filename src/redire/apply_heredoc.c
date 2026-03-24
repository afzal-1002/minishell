/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:14:15 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:14:26 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_heredoc(t_redir *redir, t_global *global)
{
	int		fd;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (setup_signals(), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		g_signal_state = 1;
		fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		if (write_heredoc_lines(fd, redir->file, global) == -1)
		{
			close(fd);
			exit(1);
		}
		close(fd);
		exit(0);
	}
	return (wait_and_prepare_heredoc(pid, redir));
}
