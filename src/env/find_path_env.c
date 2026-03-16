/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:42:18 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 14:42:19 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path_env(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
