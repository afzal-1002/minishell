/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:55 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/23 00:12:24 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_quotes(char *input, int i)
{
	char	quote;

	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	return (i);
}

int	handle_word(char *input, int i, t_token **head)
{
	int		start;
	char	*value;
	t_token	*new;

	start = i;
	while (input[i] && input[i] != ' ' && !is_operator(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
			i = handle_quotes(input, i);
		else
			i++;
	}
	value = ft_substr(input, start, i - start);
	new = new_token(value, T_WORD);
	add_token_back(head, new);
	return (i);
}
