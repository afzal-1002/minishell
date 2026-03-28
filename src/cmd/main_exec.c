/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 20:41:35 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/28 20:41:43 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_exit(t_global *global, char **env, int code)
{
	free_env(global->env);
	free_env_arr(env);
	exit(code);
}

void	exec_path(t_cmd *cmd, char **env, t_global *global)
{
	char	*path;

	if (!cmd->args || !cmd->args[0])
		child_exit(global, env, 0);
	path = find_command(cmd->args[0], global->env);
	if (!path)
	{
		print_cmd_not_found(cmd->args[0]);
		child_exit(global, env, 127);
	}
	execve(path, cmd->args, env);
	perror(path);
	free(path);
	child_exit(global, env, 126);
}

void	exec_child(t_cmd *cmd, int prev_fd, int *pipe_fd, t_global *global)
{
	char	**env;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	wire_pipes(prev_fd, pipe_fd, cmd->next != NULL);
	if (apply_redirs(cmd) == -1)
		child_exit(global, NULL, 1);
	env = rebuild_env(global->env);
	if (!env)
		child_exit(global, NULL, 1);
	exec_path(cmd, env, global);
}
