/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_or_operator_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:31:54 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/28 20:17:20 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_chain_last_segment(char *input, t_parse_state *state, t_global *global)
{
	char	*segment;
	int		ret;

	segment = trimmed_segment(input, state->start, state->i);
	if (!segment)
		return (0);
	if (!*segment)
		return (free(segment), operator_syntax_error("command"));
	ret = 1;
	if (state->should_exec && !execute_segment(segment, global))
		ret = 0;
	free(segment);
	return (ret);
}
