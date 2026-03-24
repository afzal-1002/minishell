/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:51:45 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 20:40:27 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

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
	struct termios		term;

	rl_catch_signals = 0;
	rl_bind_key('\t', rl_complete);
	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag |= (ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}
