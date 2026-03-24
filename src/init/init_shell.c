/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 16:16:20 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

static int	has_unclosed_quote(const char *input)
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

static char	*append_input_line(char *input, char *line)
{
	char	*with_newline;
	char	*joined;

	with_newline = ft_strjoin(input, "\n");
	if (!with_newline)
		return (NULL);
	joined = ft_strjoin(with_newline, line);
	free(with_newline);
	return (joined);
}

static char	*read_unclosed_quotes(char *input)
{
	char	*line;
	char	*joined;

	while (has_unclosed_quote(input))
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking for matching quote\n",
				2);
			free(input);
			return (NULL);
		}
		joined = append_input_line(input, line);
		free(line);
		free(input);
		if (!joined)
			return (NULL);
		input = joined;
	}
	return (input);
}

static int	operator_syntax_error(char *op);
static int	execute_segment(char *segment, t_global *global);
static int	run_and_or_chain(char *input, t_global *global);

static int	operator_syntax_error(char *op)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(op, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static char	*trimmed_segment(const char *input, int start, int end)
{
	while (start < end && is_blank(input[start]))
		start++;
	while (end > start && is_blank(input[end - 1]))
		end--;
	return (ft_substr(input, start, end - start));
}

static int	execute_segment(char *segment, t_global *global)
{
	t_token	*tokens;
	t_cmd	*parsed_cmd;
	int		i;
	int		single_q;
	int		double_q;
	int		paren_depth;
	char	*inner;
	int		result;

	if (!segment || !*segment)
		return (0);
	while (*segment && is_blank(*segment))
		segment++;
	if (!*segment)
		return (0);
	i = 0;
	while (segment[i] && is_blank(segment[i]))
		i++;
	if (segment[i] == '(' && segment[i + 1])
	{
		paren_depth = 0;
		single_q = 0;
		double_q = 0;
		while (segment[i])
		{
			if (segment[i] == '\'' && !double_q)
				single_q = !single_q;
			else if (segment[i] == '"' && !single_q)
				double_q = !double_q;
			else if (!single_q && !double_q)
			{
				if (segment[i] == '(')
					paren_depth++;
				else if (segment[i] == ')')
				{
					paren_depth--;
					if (paren_depth == 0)
						break ;
				}
			}
			i++;
		}
		if (paren_depth == 0 && segment[i] == ')')
		{
			inner = ft_substr(segment, 1, i - 1);
			result = run_and_or_chain(inner, global);
			free(inner);
			return (result);
		}
	}
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

static int	run_and_or_chain(char *input, t_global *global)
{
	int		start;
	int		i;
	int		single_q;
	int		double_q;
	int		paren_depth;
	int		should_exec;
	char	*segment;

	start = 0;
	while (input[start] && is_blank(input[start]))
		start++;
	if (!input[start])
		return (1);
	i = start;
	single_q = 0;
	double_q = 0;
	paren_depth = 0;
	should_exec = 1;
	while (input[i])
	{
		if (input[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (input[i] == '"' && !single_q)
			double_q = !double_q;
		else if (!single_q && !double_q)
		{
			if (input[i] == '(')
				paren_depth++;
			else if (input[i] == ')')
				paren_depth--;
			else if (paren_depth == 0 && input[i] == '&' && input[i + 1] == '&')
			{
				segment = trimmed_segment(input, start, i);
				if (!segment)
					return (0);
				if (!*segment)
					return (free(segment), operator_syntax_error("&&"));
				if (should_exec && !execute_segment(segment, global))
					return (free(segment), 0);
				free(segment);
				should_exec = (global->exit_status == 0);
				i += 2;
				while (input[i] && is_blank(input[i]))
					i++;
				start = i;
				continue ;
			}
			else if (paren_depth == 0 && input[i] == '|' && input[i + 1] == '|')
			{
				segment = trimmed_segment(input, start, i);
				if (!segment)
					return (0);
				if (!*segment)
					return (free(segment), operator_syntax_error("||"));
				if (should_exec && !execute_segment(segment, global))
					return (free(segment), 0);
				free(segment);
				should_exec = (global->exit_status != 0);
				i += 2;
				while (input[i] && is_blank(input[i]))
					i++;
				start = i;
				continue ;
			}
		}
		i++;
	}
	segment = trimmed_segment(input, start, i);
	if (!segment)
		return (0);
	if (!*segment)
		return (free(segment), operator_syntax_error("command"));
	if (should_exec && !execute_segment(segment, global))
		return (free(segment), 0);
	free(segment);
	return (1);
}

void	init_shell(t_global *global)
{
	char	*input;

	setup_signals();
	while (1)
	{
		input = readline("TESTminishell$ ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (g_signal_state == -1)
		{
			global->exit_status = 130;
			g_signal_state = 0;
		}
		input = read_unclosed_quotes(input);
		if (!input)
		{
			global->exit_status = 2;
			continue ;
		}
		if (*input)
			add_history(input);
		if (!run_and_or_chain(input, global))
			global->exit_status = 2;
		free(input);
	}
}
