/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:15 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/23 16:05:18 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "includes/minishell.h"

int	main(void)
{
	pid_t	pid;
	char	*input;
	t_token	*tokens;
	t_cmd	*parsed_cmd;
	char	*env[] = {"PATH=/usr/local/bin:/usr/bin:/bin", "HOME=/home/mafzal",
			"USER=mafzal", "SHELL=/bin/bash", NULL};

	// t_redir	*redirs;
	// int		i;
	// int		pid_id;
	pid = fork();
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
					if (pid == 0)
					{
						printf("I am CHILD\n");
						printf("My Parent PID: %d\n", getppid());
						execve("/bin/ls", parsed_cmd->args, env);
						perror("execve");
					}
					else
						wait(NULL);
					// i = 0;
					// while (parsed_cmd->args[i])
					// {
					// 	printf("  Arg[%d]: %s\n", i, parsed_cmd->args[i]);
					// 	i++;
					// }
				}
				// redirs = parsed_cmd->redirs;
				// while (redirs)
				// {
				// 	ft_printf("  Redirection: %s -> %s\n",
				// 		get_type_name(redirs->type), redirs->file);
				// 	redirs = redirs->next;
				// }
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
