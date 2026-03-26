/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_write_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 21:23:28 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/26 21:25:10 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_and_write_line(int write_fd, char *line, int expand,
		t_global *global)
{
	char	*expanded;

	expanded = line;
	if (expand)
	{
		expanded = expand_word(line, global);
		if (!expanded)
			return (-1);
	}
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	if (expand)
		free(expanded);
	return (0);
}
