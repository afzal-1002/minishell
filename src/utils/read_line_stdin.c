/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:05:56 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:18:02 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_line_stdin(void)
{
	char	buffer[1024];
	int		bytes;
	int		i;
	char	*line;

	bytes = read(1, buffer, sizeof(buffer) - 1);
	if (bytes <= 0)
		return (NULL);
	buffer[bytes] = '\0';
	i = 0;
	while (i < bytes && buffer[i] != '\n')
		i++;
	if (i < bytes)
		buffer[i] = '\0';
	if (i > 0 && buffer[i - 1] == '\r')
		buffer[i - 1] = '\0';
	line = ft_strdup(buffer);
	return (line);
}
