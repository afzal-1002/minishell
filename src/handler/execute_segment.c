/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 21:54:10 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_group_end(char *segment, int start)
{
	t_parse_state	scan;

	scan.i = start;
	scan.single_q = 0;
	scan.double_q = 0;
	scan.paren_depth = 0;
	while (segment[scan.i])
	{
		handle_single_quote(segment[scan.i], &scan.single_q, scan.double_q);
		handle_double_quote(segment[scan.i], scan.single_q, &scan.double_q);
		if (!scan.single_q && !scan.double_q)
		{
			if (segment[scan.i] == '(')
				scan.paren_depth++;
			else if (segment[scan.i] == ')')
			{
				scan.paren_depth--;
				if (scan.paren_depth == 0)
					return (scan.i);
			}
		}
		scan.i++;
	}
	return (-1);
}

static int	execute_plain_segment(char *segment, t_global *global)
{
	t_token	*tokens;
	t_cmd	*parsed_cmd;

	tokens = tokenize(segment);
	if (!tokens)
		return (0);
	global->tokens = tokens;
	parsed_cmd = parse_token(tokens, global);
	if (!parsed_cmd)
	{
		free_tokens(tokens);
		return (0);
	}
	global->cmds = parsed_cmd;
	execute(parsed_cmd, global);
	free_tokens(tokens);
	free_cmd(parsed_cmd);
	return (1);
}

char	*trimmed_segment(const char *input, int start, int end)
{
	while (start < end && is_blank(input[start]))
		start++;
	while (end > start && is_blank(input[end - 1]))
		end--;
	return (ft_substr(input, start, end - start));
}

int	execute_segment(char *segment, t_global *global)
{
	int		start;
	int		end;
	char	*inner;

	if (!segment || !*segment)
		return (0);
	start = 0;
	while (segment[start] && is_blank(segment[start]))
		start++;
	if (!segment[start])
		return (0);
	if (segment[start] == '(' && segment[start + 1])
	{
		end = find_group_end(segment, start);
		if (end > start)
		{
			inner = ft_substr(segment, start + 1, end - start - 1);
			if (!inner)
				return (0);
			end = run_and_or_chain(inner, global);
			free(inner);
			return (end);
		}
	}
	return (execute_plain_segment(segment, global));
}
