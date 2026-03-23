/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:41:59 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 18:32:49 by mgolasze         ###   ########.fr       */
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
