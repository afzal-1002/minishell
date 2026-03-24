/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:49:10 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 16:47:04 by mgolasze         ###   ########.fr       */
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

int	builtin_exit(t_cmd *cmd, t_global *global)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->args[1])
		quit(global);
	if (cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		global->exit_status = 1;
		quit(global);
	}
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		global->exit_status = 2;
		quit(global);
	}
	global->exit_status = ft_atoi(cmd->args[0]) % 256;
	if (global->exit_status < 0)
		global->exit_status += 256;
	ft_printf("exit\n");
	(void)cmd;
	quit(global);
	return (-1);
}
