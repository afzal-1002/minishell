/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:40:04 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/18 19:03:25 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_env_var(const char *src, int *i, char **out, t_global *global)
{
	int		start;
	int		j;
	char	*piece;
	char	*value;

	start = *i + 1;
	j = start;
	while (src[j] && is_var_char(src[j] ))
		j++;
	piece = ft_substr(src, start, j - start);
	value = env_value_or_empty(global, piece);
	*out = cmd_strappend(*out, value);
	free(piece);
	free(value);
	*i = j;
}
