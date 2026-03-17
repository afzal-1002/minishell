/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value_or_empty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:39:06 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/17 19:33:56 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_value_or_empty(t_global *global, const char *key)
{
	t_env	*n;

	n = env_find(global->env, (char *)key);
	if (!n || !n->value)
		return (ft_strdup(""));
	return (ft_strdup(n->value));
}
