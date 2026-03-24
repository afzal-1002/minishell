/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:41:32 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/23 16:45:40 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_delim(char *delim)
{
	int		i;
	int		j;
	char	*newdelim;

	i = 0;
	j = 0;
	while (delim[i])
	{
		if (!(delim[i] == '\'' || delim[i] == '\"'))
			j++;
		i++;
	}
	newdelim = malloc(sizeof(char) *(j + 1));
	i = 0;
	j = 0;
	while (delim[i])
	{
		if (!(delim[i] == '\'' || delim[i] == '\"'))
			newdelim[j++] = delim[i];
		i++;
	}
	newdelim[j] = '\0';
	return (newdelim);
}
