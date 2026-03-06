/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:15 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 10:00:06 by mafzal           ###   ########.fr       */
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
	t_cmd	*tmp_cmd;
	t_redir	*redirs;
	int		i;

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
		tmp_cmd = parsed_cmd;
		if (parsed_cmd)
		{
			ft_printf("Parsed Command:\n");
			while (tmp_cmd)
			{
				ft_printf("  Command: %d\n", tmp_cmd->index);
				if (tmp_cmd->args)
				{
					i = 0;
					while (tmp_cmd->args[i])
					{
						printf("  Arg[%d]: %s\n", i, tmp_cmd->args[i]);
						i++;
					}
				}
				redirs = tmp_cmd->redirs;
				while (redirs)
				{
					ft_printf("  Redirection: %s -> %s\n",
						get_type_name(redirs->type), redirs->file);
					redirs = redirs->next;
				}
				tmp_cmd = tmp_cmd->next;
			}
		}
		free_tokens(tokens);
		free_cmd(parsed_cmd);
		free(input);
	}
}
