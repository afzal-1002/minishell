/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:48:46 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/16 17:49:38 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

int	run_builtin(t_cmd *cmd, t_global *global)
{
	char	*name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	name = cmd->args[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (builtin_echo(cmd, global));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (builtin_cd(cmd, global));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(name, "export", 7) == 0)
		return (builtin_export(cmd, global));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (builtin_unset(cmd, global));
	if (ft_strncmp(name, "env", 4) == 0)
		return (builtin_env(global));
	if (ft_strncmp(name, "exit", 4) == 0)
		return (builtin_exit(cmd, global));
	return (1);
}

int	run_builtin_with_redirs(t_cmd *cmd, t_global *global)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirs(cmd) == -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	ret = run_builtin(cmd, global);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}

int	execute(t_cmd *cmds, t_global *global)
{
	if (!cmds)
		return (0);
	if (!cmds->args || !cmds->args[0])
	{
		apply_redirs(cmds);
		return(0);
	}
		if (!cmds->next && is_builtin(cmds->args[0]))
	{
		global->exit_status = run_builtin_with_redirs(cmds, global);
		return (global->exit_status);
	}
	pipe_exe(cmds, global);
	return (global->exit_status);
}
