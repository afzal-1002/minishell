/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:50:13 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/26 20:38:17 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_env_from_envp(t_global *global, char **envp)
{
	int		i;
	char	*eq;
	char	*key;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			key = ft_substr(envp[i], 0, eq - envp[i]);
			if (key)
			{
				env_set(global, key, eq + 1);
				free(key);
			}
		}
		i++;
	}
}

void	createglobal(t_global *global, char **envp)
{
	global->env = NULL;
	global->exit_status = 0;
	global->should_exit = 0;
	global->cmds = NULL;
	global->tokens = NULL;
	init_env_from_envp(global, envp);
}
