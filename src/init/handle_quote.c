/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:04:46 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 17:09:00 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_single_quote(char c, int *single_q, int double_q)
{
	if (c == '\'' && !double_q)
		*single_q = !*single_q;
}

void	handle_double_quote(char c, int single_q, int *double_q)
{
	if (c == '"' && !single_q)
		*double_q = !*double_q;
}

char	*read_unclosed_quotes(char *input)
{
	char	*line;
	char	*joined;

	while (has_unclosed_quote(input))
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: unexpected EOF\n", 2);
			free(input);
			return (NULL);
		}
		joined = append_input_line(input, line);
		free(line);
		free(input);
		if (!joined)
			return (NULL);
		input = joined;
	}
	return (input);
}
