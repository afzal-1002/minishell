/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:48:34 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 09:48:35 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cd_resolve_path(t_cmd *cmd, t_global *global)
{
	t_env	*node;
	char	*arg;

	arg = cmd->args[1];
	if (!arg || ft_strncmp(arg, "~", 2) == 0)
	{
		node = env_find(global->env, "HOME");
		if (!node || !node->value)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (node->value);
	}
	if (ft_strncmp(arg, "-", 2) == 0)
	{
		node = env_find(global->env, "OLDPWD");
		if (!node || !node->value)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		ft_putstr_fd(node->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (node->value);
	}
	return (arg);
}

void	cd_update_env(t_global *global, char *old_pwd)
{
	char	buf[PATH_MAX];

	env_set(global, "OLDPWD", old_pwd);
	if (getcwd(buf, PATH_MAX))
		env_set(global, "PWD", buf);
}

int	builtin_cd(t_cmd *cmd, t_global *global)
{
	char	old_pwd[PATH_MAX];
	char	*target;

	target = cd_resolve_path(cmd, global);
	if (!target)
		return (1);
	if (!getcwd(old_pwd, PATH_MAX))
		old_pwd[0] = '\0';
	if (chdir(target) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(target);
		return (1);
	}
	cd_update_env(global, old_pwd);
	return (0);
}
