/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:49:18 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/22 19:58:04 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(t_global *global)
{
	t_env	*cur;

	cur = global->env;
	while (cur)
	{
		ft_putstr_fd(cur->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(cur->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		cur = cur->next;
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (!getcwd(buf, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	builtin_unset(t_cmd *cmd, t_global *global)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ret = 1;
		}
		else
			env_remove(global, cmd->args[i]);
		i++;
	}
	return (ret);
}
