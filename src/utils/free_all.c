/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:22:42 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/26 20:36:26 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_global *global)
{
	free_env(global->env);
	global->env = NULL;
	free_tokens(global->tokens);
	global->tokens = NULL;
	free_cmd(global->cmds);
	global->cmds = NULL;
}
