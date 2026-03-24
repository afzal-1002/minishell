/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_or_operator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:07:05 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 17:27:23 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_chain_state(char *input, t_parse_state *state)
{
	state->start = 0;
	while (input[state->start] && is_blank(input[state->start]))
		state->start++;
	state->i = state->start;
	state->single_q = 0;
	state->double_q = 0;
	state->paren_depth = 0;
	state->should_exec = 1;
}

static int	handle_chain_char(char *input, t_parse_state *state,
		t_global *global)
{
	int	status;

	handle_single_quote(input[state->i], &state->single_q, state->double_q);
	handle_double_quote(input[state->i], state->single_q, &state->double_q);
	if (!state->single_q && !state->double_q)
	{
		status = handle_unquoted_block(input, &state->i, &state->paren_depth,
				&state->start, &state->should_exec, global);
		if (status == -1)
			return (-1);
		if (status == 1)
			return (1);
	}
	state->i++;
	return (0);
}

static int	run_chain_last_segment(char *input, t_parse_state *state,
		t_global *global)
{
	char	*segment;

	segment = trimmed_segment(input, state->start, state->i);
	if (!segment)
		return (0);
	if (!*segment)
		return (free(segment), operator_syntax_error("command"));
	if (state->should_exec && !execute_segment(segment, global))
		return (free(segment), 0);
	free(segment);
	return (1);
}

int	run_and_or_chain(char *input, t_global *global)
{
	t_parse_state	state;
	int				status;

	init_chain_state(input, &state);
	if (!input[state.start])
		return (1);
	while (input[state.i])
	{
		status = handle_chain_char(input, &state, global);
		if (status == -1)
			return (0);
	}
	return (run_chain_last_segment(input, &state, global));
}

int	handle_or_operator(char *input, int *start, int *i, int *should_exec,
		t_global *global)
{
	char	*segment;

	if (!(input[*i] == '|' && input[*i + 1] == '|'))
		return (0);
	segment = trimmed_segment(input, *start, *i);
	if (!segment)
		return (-1);
	if (!*segment)
		return (free(segment), operator_syntax_error("||"), -1);
	if (*should_exec && !execute_segment(segment, global))
		return (free(segment), -1);
	free(segment);
	*should_exec = (global->exit_status != 0);
	*i += 2;
	while (input[*i] && is_blank(input[*i]))
		(*i)++;
	*start = *i;
	return (1);
}
int	handle_and_operator(char *input, int *start, int *i, int *should_exec,
		t_global *global)
{
	char *segment;

	if (!(input[*i] == '&' && input[*i + 1] == '&'))
		return (0);
	segment = trimmed_segment(input, *start, *i);
	if (!segment)
		return (-1);
	if (!*segment)
		return (free(segment), operator_syntax_error("&&"), -1);
	if (*should_exec && !execute_segment(segment, global))
		return (free(segment), -1);
	free(segment);
	*should_exec = (global->exit_status == 0);
	*i += 2;
	while (input[*i] && is_blank(input[*i]))
		(*i)++;
	*start = *i;
	return (1);
}