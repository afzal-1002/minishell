/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:15 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/22 23:24:16 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "includes/minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*parsed_cmd;
	int		i;
	t_redir	*redirs;

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
		ft_printf("\n--- TOKENS ---\n");
		print_tokens(tokens);
		ft_printf("--------------\n\n");
		parsed_cmd = parse_token(tokens);
		if (parsed_cmd)
		{
			ft_printf("Parsed Command:\n");
			while (parsed_cmd)
			{
				ft_printf("  Command: %d\n", parsed_cmd->index);
				if (parsed_cmd->args)
				{
					i = 0;
					while (parsed_cmd->args[i])
					{
						printf("  Arg[%d]: %s\n", i, parsed_cmd->args[i]);
						i++;
					}
				}
				redirs = parsed_cmd->redirs;
				while (redirs)
				{
					ft_printf("  Redirection: %s -> %s\n",
						get_type_name(redirs->type), redirs->file);
					redirs = redirs->next;
				}
				parsed_cmd = parsed_cmd->next;
			}
			ft_printf("\n");
		}
		free_tokens(tokens);
		free_cmd(parsed_cmd);
		free(input);
	}
	return (0);
}
