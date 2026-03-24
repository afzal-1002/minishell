/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 21:57:09 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:03:54 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	prepare_heredoc(pid_t pid, t_redir *redir)
{
	int		status;
	char	*old_file;

	if (waitpid(pid, &status, 0) == -1)
		return (setup_signals(), -1);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_signal_state = -1;
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		g_signal_state = -1;
		return (-1);
	}
	old_file = redir->file;
	redir->file = ft_strdup(".heredoc_tmp");
	free(old_file);
	if (!redir->file)
		return (-1);
	return (0);
}
