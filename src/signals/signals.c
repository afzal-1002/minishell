/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:51:45 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 22:17:47 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_signal_state;

static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal_state == 1)
	{
		g_signal_state = -1;
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	g_signal_state = -1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction	sa_int;

	rl_bind_key('\t', rl_complete);
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}
