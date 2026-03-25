/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:14:16 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:13:06 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_unquoted_block(char *input, t_parse_state *state, t_global *global)
{
	int	handled;

	if (input[state->i] == '(')
		state->paren_depth++;
	else if (input[state->i] == ')')
		state->paren_depth--;
	else if (state->paren_depth == 0)
	{
		handled = handle_and_operator(input, state, global);
		if (handled == -1)
			return (-1);
		if (handled == 1)
			return (1);
		handled = handle_or_operator(input, state, global);
		if (handled == -1)
			return (-1);
		if (handled == 1)
			return (1);
	}
	return (0);
}
