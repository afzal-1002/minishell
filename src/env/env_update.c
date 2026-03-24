/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:41:26 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 12:51:31 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_update(t_env *node, char *value)
{
	char	*new_val;

	new_val = ft_strdup(value);
	if (!new_val)
		return ;
	free(node->value);
	node->value = new_val;
}
