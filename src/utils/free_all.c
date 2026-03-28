/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:22:42 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/28 19:34:01 by mgolasze         ###   ########.fr       */
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
	free(global->input);
	global->input = NULL;
}
