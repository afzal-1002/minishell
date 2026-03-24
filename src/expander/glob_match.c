/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:10:00 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 19:55:32 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	glob_match_pattern(const char *pattern, const char *name)
{
	if (*pattern == '\0')
		return (*name == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*name)
		{
			if (glob_match_pattern(pattern, name))
				return (1);
			name++;
		}
		return (0);
	}
	if (*pattern == '?')
		return (*name && glob_match_pattern(pattern + 1, name + 1));
	if (*pattern != *name)
		return (0);
	return (glob_match_pattern(pattern + 1, name + 1));
}
