/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:49:10 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/26 21:18:53 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_numeric(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	exit_numeric_error(char *arg, t_global *global)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	global->exit_status = 2;
	global->should_exit = 1;
	ft_printf("exit\n");
	return (-1);
}

int	builtin_exit(t_cmd *cmd, t_global *global)
{
	if (!cmd->args[1])
	{
		global->should_exit = 1;
		ft_printf("exit\n");
		return (-1);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		global->exit_status = 1;
		return (1);
	}
	if (!is_numeric(cmd->args[1]))
		return (exit_numeric_error(cmd->args[1], global));
	global->exit_status = ft_atoi(cmd->args[1]) % 256;
	if (global->exit_status < 0)
		global->exit_status += 256;
	global->should_exit = 1;
	ft_printf("exit\n");
	return (-1);
}
