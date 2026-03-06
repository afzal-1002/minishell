/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:48:34 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 14:37:00 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*cd_get_env_value(t_env *env_node, const char *err_msg)
{
	if (!env_node || !env_node->value)
	{
		ft_putstr_fd(err_msg, STDERR_FILENO);
		return (NULL);
	}
	return (env_node->value);
}

char	*cd_resolve_path(t_cmd *cmd, t_global *global)
{
	t_env	*node;
	char	*arg;

	arg = cmd->args[1];
	if (!arg || ft_strncmp(arg, "~", 2) == 0)
	{
		node = env_find(global->env, "HOME");
		return (cd_get_env_value(node, "cd: HOME not set\n"));
	}
	if (ft_strncmp(arg, "-", 2) == 0)
	{
		node = env_find(global->env, "OLDPWD");
		arg = cd_get_env_value(node, "cd: OLDPWD not set\n");
		if (!arg)
			return (NULL);
		ft_putstr_fd(arg, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (arg);
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
