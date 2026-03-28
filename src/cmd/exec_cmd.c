/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:49:46 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/28 20:41:54 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wire_pipes(int prev_fd, int *pipe_fd, int has_next)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (has_next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
	}
}

void	print_cmd_not_found(char *name)
{
	write(2, name, ft_strlen(name));
	write(2, ": command not found\n", 20);
}

static void	child_cleanup_exit(char **env, char *path, t_global *global,
		int code)
{
	free(path);
	free_env_arr(env);
	free_all(global);
	exit(code);
}

static void	handle_cmd_not_found(t_cmd *cmd, char **env, t_global *global)
{
	print_cmd_not_found(cmd->args[0]);
	child_cleanup_exit(env, NULL, global, 127);
}

void	exec_child(t_cmd *cmd, int prev_fd, int *pipe_fd, t_global *global)
{
	char	**env;
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	wire_pipes(prev_fd, pipe_fd, cmd->next != NULL);
	if (apply_redirs(cmd) == -1)
		child_cleanup_exit(NULL, NULL, global, 1);
	env = rebuild_env(global->env);
	if (!env || !cmd->args || !cmd->args[0])
		child_cleanup_exit(env, NULL, global, !env);
	path = find_command(cmd->args[0], global->env);
	if (!path)
		handle_cmd_not_found(cmd, env, global);
	execve(path, cmd->args, env);
	perror(path);
	child_cleanup_exit(env, path, global, 126);
}
