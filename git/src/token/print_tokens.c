/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:34 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/11 18:46:17 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("Value: %s  Type: %s\n", tokens->value,
			get_type_name(tokens->type));
		tokens = tokens->next;
	}
}
