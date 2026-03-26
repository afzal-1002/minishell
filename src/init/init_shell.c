/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/26 21:21:18 by mafzal           ###   ########.fr       */
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

static int	check_input(char *input)
{
	if (!input)
	{
		ft_printf("exit\n");
		return (1);
	}
	return (0);
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

void	init_shell(t_global *global)
{
	char	*input;

	setup_signals();
	while (1)
	{
		if (g_signal_state == -1)
		{
			global->exit_status = 130;
			g_signal_state = 0;
		}
		input = readline(PROMPT);
		if (check_input(input))
			break ;
		input = read_unclosed_quotes(input);
		if (!handle_shell_input(input, global))
			continue ;
		free(input);
		if (global->should_exit)
			break ;
	}
}
