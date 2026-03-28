/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/28 20:21:02 by mgolasze         ###   ########.fr       */
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

static void	free_cmd_and_tokens(t_global *global)
{
	free_tokens(global->tokens);
	global->tokens = NULL;
	free_cmd(global->cmds);
	global->cmds = NULL;
}

static int	execute_plain_segment(char *segment, t_global *global)
{
	free_cmd_and_tokens(global);
	global->tokens = tokenize(segment);
	if (!global->tokens)
		return (0);
	global->cmds = parse_token(global->tokens, global);
	if (!global->cmds)
	{
		free_cmd_and_tokens(global);
		return (0);
	}
	execute(global->cmds, global);
	free_cmd_and_tokens(global);
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
