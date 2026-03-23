/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 16:48:15 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/23 16:48:39 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute(t_cmd *cmds, t_global *global)
{
	int	saved_stdin;

	if (!cmds)
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	process_heredoc(cmds, global);
	if (!cmds->args || !cmds->args[0])
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return (0);
	}
	if (!cmds->next && is_builtin(cmds->args[0]))
	{
		global->exit_status = run_builtin_with_redirs(cmds, global);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return (global->exit_status);
	}
	pipe_exe(cmds, global);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (global->exit_status);
}
