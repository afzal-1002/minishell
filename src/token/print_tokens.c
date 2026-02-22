/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:34 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/22 23:57:48 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "ft_printf.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("Value: %s | Type: %s\n", tokens->value,
			get_type_name(tokens->type));
		tokens = tokens->next;
	}
}
