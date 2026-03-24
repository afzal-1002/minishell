/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unclosed_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:44:17 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 19:15:41 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_unclosed_quote(const char *input)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (input[i] == '"' && !single_q)
			double_q = !double_q;
		i++;
	}
	return (single_q || double_q);
}
