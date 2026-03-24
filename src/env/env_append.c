/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:41:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 18:33:31 by mgolasze         ###   ########.fr       */
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
