/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:55 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/17 23:34:27 by mafzal           ###   ########.fr       */
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

static char	*strip_quotes(char *value)
{
	char	*stripped;
	int		len;

	len = ft_strlen(value);
	if (len >= 2 && ((value[0] == '\'' && value[len - 1] == '\'')
			|| (value[0] == '"' && value[len - 1] == '"')))
	{
		stripped = ft_substr(value, 1, len - 2);
		free(value);
		return (stripped);
	}
	return (value);
}

static t_token_type	get_quote_type(char *value)
{
	int	len;

	len = ft_strlen(value);
	if (len >= 2)
	{
		if (value[0] == '\'' && value[len - 1] == '\'')
			return (T_SINGLE_QUOTE);
		if (value[0] == '"' && value[len - 1] == '"')
			return (T_DOUBLE_QUOTE);
	}
	return (T_WORD);
}

int	handle_word(char *input, int i, t_token **head)
{
	int				start;
	char			*value;
	t_token			*new;
	t_token_type	type;

	start = i;
	while (input[i] && input[i] != ' ' && !is_operator(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
			i = handle_quotes(input, i);
		else
			i++;
	}
	value = ft_substr(input, start, i - start);
	type = get_quote_type(value);
	value = strip_quotes(value);
	new = new_token(value, type);
	add_token_back(head, new);
	return (i);
}
