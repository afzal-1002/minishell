/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:41:31 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/25 18:23:29 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_ret(char **ret, int i)
{
	while (i >= 0)
	{
		free(ret[i]);
		i--;
	}
	free(ret);
}

char	**rebuild_env(t_env *env)
{
	char	**ret;
	t_env	*tmp;
	int		i;

	ret = malloc(sizeof(char *) * (env_list_len(env) + 1));
	if (!ret)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			ret[i] = env_join_kv(tmp->key, tmp->value);
			if (!ret[i])
				return (free_ret(ret, i), NULL);
			i++;
		}
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}
