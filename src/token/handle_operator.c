/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:58 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/11 18:46:22 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_operator(char *input, int i, t_token **head)
{
	t_token			*new;
	t_token_type	type;
	char			*value;
	int				len;

	type = get_operator_type(input, i);
	if (ft_isdigit(input[i]) && input[i + 1] == '>')
	{
		if (input[i + 2] == '>')
			len = 3;
		else
			len = 2;
	}
	else if (type == T_HEREDOC || type == T_REDIR_APPEND)
		len = 2;
	else
		len = 1;
	value = ft_substr(input, i, len);
	new = new_token(value, type);
	if (!new)
	{
    	free(value);
    	return (i + len);
	}
	add_token_back(head, new);
	return (i + len);
}
