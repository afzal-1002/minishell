/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:58 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/23 16:07:25 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "libft.h"

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
	add_token_back(head, new);
	return (i + len);
}
