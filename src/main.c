/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:15 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 11:13:53 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "includes/minishell.h"

void	startloop(t_global *global);

int	main(int argc, char **argv, char **envp)
{
	t_global	global;

	(void)argc;
	(void)argv;
	createglobal(&global, envp);
	startloop(&global);
	return (0);
}

void	startloop(t_global *global)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*parsed_cmd;

	setup_signals();
	(void)global;
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
		parsed_cmd = parse_token(tokens);
		if (parsed_cmd)
			execute(parsed_cmd, global);
		free_tokens(tokens);
		free_cmd(parsed_cmd);
		free(input);
	}
}
