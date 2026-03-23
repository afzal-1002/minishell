/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:49:46 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 20:32:32 by mgolasze         ###   ########.fr       */
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
		//close(pipe_fd[1]);
	}
}

void	print_cmd_not_found(char *name)
{
	write(2, name, ft_strlen(name));
	write(2, ": command not found\n", 20);
}

void	exec_child(t_cmd *cmd, int prev_fd, int *pipe_fd, t_global *global)
{
	char	**env;
	char	*path;

	wire_pipes(prev_fd, pipe_fd, cmd->next != NULL);
	if (apply_redirs(cmd) == -1)
		exit(1);
	env = rebuild_env(global->env);
	if (!env)
		exit(1);
	if (!cmd->args || !cmd->args[0])
	{
		free_env_arr(env);
		exit(0);
	}
	path = find_command(cmd->args[0], global->env);
	if (!path)
	{
		print_cmd_not_found(cmd->args[0]);
		free_env_arr(env);
		exit(127);
	}
	execve(path, cmd->args, env);
	perror(path);
	free(path);
	free_env_arr(env);
	exit(126);
}
