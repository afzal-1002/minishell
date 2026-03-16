/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:44 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/23 16:06:27 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*tokenize(char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (ft_isdigit(input[i]) && input[i + 1] == '>')
			i = handle_operator(input, i, &head);
		else if (is_operator(input[i]))
			i = handle_operator(input, i, &head);
		else
			i = handle_word(input, i, &head);
	}
	return (head);
}
