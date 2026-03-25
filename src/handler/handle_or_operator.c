/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_or_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:27:28 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:27:50 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_or_operator(char *input, t_parse_state *state, t_global *global)
{
	char	*segment;

	if (!(input[state->i] == '|' && input[state->i + 1] == '|'))
		return (0);
	segment = trimmed_segment(input, state->start, state->i);
	if (!segment)
		return (-1);
	if (!*segment)
		return (free(segment), operator_syntax_error("||"), -1);
	if (state->should_exec && !execute_segment(segment, global))
		return (free(segment), -1);
	free(segment);
	state->should_exec = (global->exit_status != 0);
	state->i += 2;
	while (input[state->i] && is_blank(input[state->i]))
		state->i++;
	state->start = state->i;
	return (1);
}
