/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:41:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 14:41:39 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_append(t_global *global, t_env *node)
{
	t_env	*cur;

	if (!global->env)
	{
		global->env = node;
		return ;
	}
	cur = global->env;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}
