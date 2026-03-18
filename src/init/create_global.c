/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_global.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:50:13 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/17 22:15:42 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_global(t_global *global, char **envp)
{
	global->env = NULL;
	global->exit_status = 0;
	global->signal_received = 0;
	global->cmds = NULL;
	global->tokens = NULL;
	init_env_from_envp(global, envp);
}
