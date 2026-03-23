/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_plain_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:41:09 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/16 22:42:31 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_plain_char(const char *src, int *i, char **out)
{
	char	*piece;

	piece = ft_substr(src, *i, 1);
	*out = cmd_strappend(*out, piece);
	free(piece);
	(*i)++;
}
