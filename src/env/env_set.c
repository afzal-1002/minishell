/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:41:59 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 14:42:00 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_set(t_global *global, char *key, char *value)
{
	t_env	*node;

	node = env_find(global->env, key);
	if (node)
	{
		env_update(node, value);
		return (0);
	}
	node = env_new_node(key, value);
	if (!node)
		return (0);
	env_append(global, node);
	return (node);
}
