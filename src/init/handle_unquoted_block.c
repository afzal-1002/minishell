/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unquoted_block.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:14:16 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 17:14:35 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_unquoted_block(char *input, int *i, int *paren_depth,
		int *start, int *should_exec, t_global *global)
{
	int	handled;

	if (input[*i] == '(')
		(*paren_depth)++;
	else if (input[*i] == ')')
		(*paren_depth)--;
	else if (*paren_depth == 0)
	{
		handled = handle_and_operator(input, start, i, should_exec, global);
		if (handled == -1)
			return (-1);
		if (handled == 1)
			return (1);
		handled = handle_or_operator(input, start, i, should_exec, global);
		if (handled == -1)
			return (-1);
		if (handled == 1)
			return (1);
	}
	return (0);
}
