/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:05:56 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/25 17:59:57 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_line_stdin(void)
{
	char	buffer[1024];
	int		bytes;
	int		i;
	char	*line;

	bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
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
