/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 16:48:15 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/26 20:38:36 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_single_builtin(t_cmd *cmds, t_global *global, int saved_stdin)
{
	int	ret;

	if (!cmds->next && cmds->args && cmds->args[0] && is_builtin(cmds->args[0]))
	{
		close(saved_stdin);
		ret = run_builtin_with_redirs(cmds, global);
		if (ret != -1)
			global->exit_status = ret;
		return (1);
	}
	return (0);
}

int	execute(t_cmd *cmds, t_global *global)
{
	int	saved_stdin;

	if (!cmds)
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	if (process_heredoc(cmds, global) == -1 || g_signal_state == -1)
	{
		global->exit_status = 130;
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return (global->exit_status);
	}
	if ((!cmds->args || !cmds->args[0]) && !cmds->next)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return (0);
	}
	if (exec_single_builtin(cmds, global, saved_stdin))
		return (global->exit_status);
	pipe_exe(cmds, global);
	setup_signals();
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (global->exit_status);
}
