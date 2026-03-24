/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 21:54:52 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*append_input_line(char *input, char *line)
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

static int	check_input(char *input)
{
	if (!input)
	{
		ft_printf("exit\n");
		return (1);
	}
	return (0);
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
		input = readline("TESTminishell$ ");
		if (check_input(input))
			break ;
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
