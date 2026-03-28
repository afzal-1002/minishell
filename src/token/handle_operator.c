/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:48 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/28 20:43:52 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_operator_len(char *input, int i, t_token_type type)
{
	if (ft_isdigit(input[i]) && input[i + 1] == '>')
		return (2 + (input[i + 2] == '>'));
	if (type == T_HEREDOC || type == T_REDIR_APPEND)
		return (2);
	return (1);
}

int	handle_operator(char *input, int i, t_token **head)
{
	t_token			*new;
	t_token_type	type;
	char			*value;
	int				len;

	type = get_operator_type(input, i);
	len = get_operator_len(input, i, type);
	value = ft_substr(input, i, len);
	new = new_token(value, type);
	if (!new)
		return (free(value), i + len);
	add_token_back(head, new);
	return (i + len);
}
