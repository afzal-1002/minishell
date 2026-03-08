/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/08 19:04:26 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "ft_printf.h"

void	init_shell(t_global *global)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*parsed_cmd;

	// char	**cmd_name;
	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
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
		parsed_cmd = parse_token(tokens);
		if (parsed_cmd)
		{
			global->cmds = parsed_cmd;
			print_cmd(parsed_cmd);
			print_tokens(tokens);
			// execute(parsed_cmd, global);
		}
		free_tokens(tokens);
		free_cmd(parsed_cmd);
		free(input);
	}
}
