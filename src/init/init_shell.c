/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:38 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/17 17:00:55 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(t_global *global)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*parsed_cmd;

	// t_cmd	*next;
	// char	**args;
	// t_cmd	*tmp;
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
		parsed_cmd = parse_token(tokens, global);
		// tmp = parsed_cmd;
		// while (tmp)
		// {
		// 	next = tmp->next;
		// 	ft_printf("Command index: %d\n", tmp->index);
		// 	args = tmp->args;
		// 	for (int i = 0; args && args[i]; i++)
		// 		ft_printf("  Arg %d: %s\n", i, args[i]);
		// 	tmp = next;
		// }
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
