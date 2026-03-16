/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:41:31 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 14:42:24 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**rebuild_env(t_env *env)
{
	char	**ret;
	t_env	*tmp;
	int		i;

	i = env_list_len(env);
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		ret[i] = env_join_kv(tmp->key, tmp->value);
		if (!ret[i])
		{
			while (i-- > 0)
				free(ret[i]);
			free(ret);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}
