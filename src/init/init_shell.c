/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/28 19:40:33 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*append_input_line(char *input, char *line)
{
	char	*newline;
	char	*joined;

	newline = ft_strjoin(input, "\n");
	if (!newline)
		return (NULL);
	joined = ft_strjoin(newline, line);
	free(newline);
	return (joined);
}

static int	handle_shell_input(char *input, t_global *global)
{
	if (!input)
	{
		global->exit_status = 2;
		return (0);
	}
	if (*input)
		add_history(input);
	if (!run_and_or_chain(input, global))
		global->exit_status = 2;
	return (1);
}

static int	check_input(char *input)
{
	if (!input)
		return (ft_printf("exit\n"), 1);
	return (0);
}

static void	handle_signal_state(t_global *global)
{
	if (g_signal_state == -1)
	{
		global->exit_status = 130;
		g_signal_state = 0;
	}
}

void	init_shell(t_global *global)
{
	char	*input;

	setup_signals();
	global->input = NULL;
	while (1)
	{
		handle_signal_state(global);
		input = readline(PROMPT);
		if (check_input(input))
			break ;
		global->input = read_unclosed_quotes(input);
		if (!handle_shell_input(global->input, global))
		{
			free(global->input);
			global->input = NULL;
			continue ;
		}
		free(global->input);
		global->input = NULL;
		if (global->should_exit)
			break ;
	}
}
