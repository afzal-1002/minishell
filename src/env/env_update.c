/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:41:26 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/28 19:03:14 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_update(t_env *node, char *value)
{
	char	*new_val;

	if (!value)
		return ;
	new_val = ft_strdup(value);
	if (!new_val)
		return ;
	free(node->value);
	node->value = new_val;
}
