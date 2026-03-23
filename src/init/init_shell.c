/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 22:12:56 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(t_global *global)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*parsed_cmd;

	setup_signals();
	while (1)
	{
		input = readline("OURminishell$ ");
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
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		if (tokens)
			global->tokens = tokens;
		parsed_cmd = parse_token(tokens, global);
		if (parsed_cmd)
		{
			global->cmds = parsed_cmd;
			execute(parsed_cmd, global);
		}
		free_tokens(tokens);
		free_cmd(parsed_cmd);
		free(input);
	}
}
