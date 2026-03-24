/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:48:51 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 18:04:58 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (i > 1 && arg[i] == '\0');
}

int	echo_print(char **args, int start, int newline)
{
	int	i;

	i = start;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	builtin_echo(t_cmd *cmd, t_global *global)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	(void)global;
	if (!cmd->args)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	return (echo_print(cmd->args, i, newline));
}
